#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_4__ {int id; scalar_t__ pix_fmt; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ AVHWAccel ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_DXVA2_VLD ; 
 scalar_t__ AV_PIX_FMT_VAAPI_VLD ; 
 scalar_t__ AV_PIX_FMT_VDTOOL ; 
 TYPE_1__* av_hwaccel_next (TYPE_1__*) ; 
 int /*<<< orphan*/ * avcodec_find_decoder_by_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static AVCodec *find_hardware_decoder(enum AVCodecID id)
{
	AVHWAccel *hwa = av_hwaccel_next(NULL);
	AVCodec *c = NULL;

	while (hwa) {
		if (hwa->id == id) {
			if (hwa->pix_fmt == AV_PIX_FMT_VDTOOL ||
				hwa->pix_fmt == AV_PIX_FMT_DXVA2_VLD ||
			    hwa->pix_fmt == AV_PIX_FMT_VAAPI_VLD) {
				c = avcodec_find_decoder_by_name(hwa->name);
				if (c)
					break;
			}
		}

		hwa = av_hwaccel_next(hwa);
	}

	return c;
}