#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  bitstream; } ;
typedef  TYPE_1__ WebPMuxFrameInfo ;
typedef  int /*<<< orphan*/  WebPMuxError ;
typedef  int /*<<< orphan*/  WebPMuxAnimParams ;
typedef  int /*<<< orphan*/  WebPMux ;
typedef  int /*<<< orphan*/  WebPIterator ;
typedef  int /*<<< orphan*/  WebPDemuxer ;
typedef  scalar_t__ WebPDemuxState ;
struct TYPE_10__ {size_t size; int /*<<< orphan*/ * bytes; } ;
typedef  TYPE_2__ WebPData ;
typedef  int /*<<< orphan*/  WebPChunkIterator ;

/* Variables and functions */
 scalar_t__ WEBP_DEMUX_PARSED_HEADER ; 
 int /*<<< orphan*/  WEBP_MUX_NOT_FOUND ; 
 int /*<<< orphan*/  WEBP_MUX_OK ; 
 int /*<<< orphan*/  WebPDataClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPDataInit (TYPE_2__*) ; 
 int /*<<< orphan*/ * WebPDemux (TYPE_2__*) ; 
 int /*<<< orphan*/  WebPDemuxDelete (int /*<<< orphan*/ *) ; 
 scalar_t__ WebPDemuxGetChunk (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ WebPDemuxGetFrame (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPDemuxNextChunk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPDemuxNextFrame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WebPDemuxPartial (TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  WebPDemuxPrevChunk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPDemuxReleaseChunkIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPDemuxReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WebPMuxCreate (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  WebPMuxDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPMuxGetAnimationParams (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPMuxGetChunk (int /*<<< orphan*/ *,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  WebPMuxGetFeatures (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPMuxGetFrame (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int kFuzzFrameLimit ; 

int LLVMFuzzerTestOneInput(const uint8_t* const data, size_t size) {
  WebPData webp_data;
  WebPDataInit(&webp_data);
  webp_data.size = size;
  webp_data.bytes = data;

  // Extracted chunks and frames are not processed or decoded,
  // which is already covered extensively by the other fuzz targets.

  if (size & 1) {
    // Mux API
    WebPMux* mux = WebPMuxCreate(&webp_data, size & 2);
    if (!mux) return 0;

    WebPData chunk;
    WebPMuxGetChunk(mux, "EXIF", &chunk);
    WebPMuxGetChunk(mux, "ICCP", &chunk);
    WebPMuxGetChunk(mux, "FUZZ", &chunk);  // unknown

    uint32_t flags;
    WebPMuxGetFeatures(mux, &flags);

    WebPMuxAnimParams params;
    WebPMuxGetAnimationParams(mux, &params);

    WebPMuxError status;
    WebPMuxFrameInfo info;
    for (int i = 0; i < kFuzzFrameLimit; i++) {
      status = WebPMuxGetFrame(mux, i + 1, &info);
      if (status == WEBP_MUX_NOT_FOUND) {
        break;
      } else if (status == WEBP_MUX_OK) {
        WebPDataClear(&info.bitstream);
      }
    }

    WebPMuxDelete(mux);
  } else {
    // Demux API
    WebPDemuxer* demux;
    if (size & 2) {
      WebPDemuxState state;
      demux = WebPDemuxPartial(&webp_data, &state);
      if (state < WEBP_DEMUX_PARSED_HEADER) {
        WebPDemuxDelete(demux);
        return 0;
      }
    } else {
      demux = WebPDemux(&webp_data);
      if (!demux) return 0;
    }

    WebPChunkIterator chunk_iter;
    if (WebPDemuxGetChunk(demux, "EXIF", 1, &chunk_iter)) {
      WebPDemuxNextChunk(&chunk_iter);
    }
    WebPDemuxReleaseChunkIterator(&chunk_iter);
    if (WebPDemuxGetChunk(demux, "ICCP", 0, &chunk_iter)) {  // 0 == last
      WebPDemuxPrevChunk(&chunk_iter);
    }
    WebPDemuxReleaseChunkIterator(&chunk_iter);
    // Skips FUZZ because the Demux API has no concept of (un)known chunks.

    WebPIterator iter;
    if (WebPDemuxGetFrame(demux, 1, &iter)) {
      for (int i = 1; i < kFuzzFrameLimit; i++) {
        if (!WebPDemuxNextFrame(&iter)) break;
      }
    }

    WebPDemuxReleaseIterator(&iter);
    WebPDemuxDelete(demux);
  }

  return 0;
}