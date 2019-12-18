#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/  size; int /*<<< orphan*/  bytes; } ;
struct TYPE_13__ {TYPE_1__ fragment; } ;
typedef  TYPE_2__ WebPIterator ;
typedef  int /*<<< orphan*/  WebPDemuxer ;
struct TYPE_14__ {size_t size; int /*<<< orphan*/ * bytes; } ;
typedef  TYPE_3__ WebPData ;
struct TYPE_15__ {size_t use_threads; scalar_t__ color_mode; } ;
typedef  TYPE_4__ WebPAnimDecoderOptions ;
typedef  int /*<<< orphan*/  WebPAnimDecoder ;
typedef  scalar_t__ WEBP_CSP_MODE ;

/* Variables and functions */
 scalar_t__ MODE_BGRA ; 
 size_t MODE_LAST ; 
 scalar_t__ MODE_RGBA ; 
 scalar_t__ MODE_bgrA ; 
 scalar_t__ MODE_rgbA ; 
 int /*<<< orphan*/  WEBP_FF_CANVAS_HEIGHT ; 
 int /*<<< orphan*/  WEBP_FF_CANVAS_WIDTH ; 
 int /*<<< orphan*/  WebPAnimDecoderDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WebPAnimDecoderGetNext (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/ * WebPAnimDecoderNew (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  WebPAnimDecoderOptionsInit (TYPE_4__*) ; 
 int /*<<< orphan*/  WebPDataInit (TYPE_3__*) ; 
 int /*<<< orphan*/ * WebPDemux (TYPE_3__*) ; 
 int /*<<< orphan*/  WebPDemuxDelete (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  WebPDemuxGetFrame (int /*<<< orphan*/ * const,int,TYPE_2__*) ; 
 size_t WebPDemuxGetI (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WebPDemuxReleaseIterator (TYPE_2__*) ; 
 scalar_t__ WebPGetInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int kFuzzFrameLimit ; 
 size_t kFuzzPxLimit ; 

int LLVMFuzzerTestOneInput(const uint8_t* const data, size_t size) {
  WebPData webp_data;
  WebPDataInit(&webp_data);
  webp_data.size = size;
  webp_data.bytes = data;

  // WebPAnimDecoderNew uses WebPDemux internally to calloc canvas size.
  WebPDemuxer* const demux = WebPDemux(&webp_data);
  if (!demux) return 0;
  const uint32_t cw = WebPDemuxGetI(demux, WEBP_FF_CANVAS_WIDTH);
  const uint32_t ch = WebPDemuxGetI(demux, WEBP_FF_CANVAS_HEIGHT);
  if ((size_t)cw * ch > kFuzzPxLimit) {
    WebPDemuxDelete(demux);
    return 0;
  }

  // In addition to canvas size, check each frame separately.
  WebPIterator iter;
  for (int i = 0; i < kFuzzFrameLimit; i++) {
    if (!WebPDemuxGetFrame(demux, i + 1, &iter)) break;
    int w, h;
    if (WebPGetInfo(iter.fragment.bytes, iter.fragment.size, &w, &h)) {
      if ((size_t)w * h > kFuzzPxLimit) {  // image size of the frame payload
        WebPDemuxReleaseIterator(&iter);
        WebPDemuxDelete(demux);
        return 0;
      }
    }
  }

  WebPDemuxReleaseIterator(&iter);
  WebPDemuxDelete(demux);

  WebPAnimDecoderOptions dec_options;
  if (!WebPAnimDecoderOptionsInit(&dec_options)) return 0;

  dec_options.use_threads = size & 1;
  // Animations only support 4 (of 12) modes.
  dec_options.color_mode = (WEBP_CSP_MODE)(size % MODE_LAST);
  if (dec_options.color_mode != MODE_BGRA &&
      dec_options.color_mode != MODE_rgbA &&
      dec_options.color_mode != MODE_bgrA) {
    dec_options.color_mode = MODE_RGBA;
  }

  WebPAnimDecoder* dec = WebPAnimDecoderNew(&webp_data, &dec_options);
  if (!dec) return 0;

  for (int i = 0; i < kFuzzFrameLimit; i++) {
    uint8_t* buf;
    int timestamp;
    if (!WebPAnimDecoderGetNext(dec, &buf, &timestamp)) break;
  }

  WebPAnimDecoderDelete(dec);
  return 0;
}