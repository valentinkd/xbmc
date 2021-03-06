#pragma once
/*
 *      Copyright (C) 2012-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "DVDDemux.h"

#ifdef TARGET_WINDOWS
#define __attribute__(dummy_val)
#pragma pack(push)
#pragma pack(1)
#endif

typedef struct
{
  char fourcc[4];
  uint32_t type;
  uint32_t channels;
  uint32_t sampleRate;
  uint32_t bitsPerSample;
  uint64_t durationMs;
} __attribute__((__packed__)) Demux_BXA_FmtHeader;

#ifdef TARGET_WINDOWS
#pragma pack(pop)
#endif

#include <vector>

#define BXA_PACKET_TYPE_FMT_DEMUX 1

class CDemuxStreamAudioBXA;

class CDVDDemuxBXA : public CDVDDemux
{
public:

  CDVDDemuxBXA();
  ~CDVDDemuxBXA() override;

  bool Open(CDVDInputStream* pInput);
  void Dispose();
  bool Reset() override;
  void Abort() override;
  void Flush() override;
  DemuxPacket* Read() override;
  bool SeekTime(double time, bool backwards = false, double* startpts = NULL) override { return false; }
  int GetStreamLength() override { return (int)m_header.durationMs; }
  CDemuxStream* GetStream(int iStreamId) const override;
  std::vector<CDemuxStream*> GetStreams() const override;
  int GetNrOfStreams() const override;
  std::string GetFileName() override;
  std::string GetStreamCodecName(int iStreamId) override;

protected:
  friend class CDemuxStreamAudioBXA;
  CDVDInputStream* m_pInput;
  int64_t m_bytes;

  CDemuxStreamAudioBXA *m_stream;

  Demux_BXA_FmtHeader m_header;
};

