#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ codec_id; } ;
struct TYPE_7__ {scalar_t__ id; scalar_t__ pix_fmt; } ;
typedef  TYPE_1__ AVHWAccel ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_DXVA2_VLD ; 
 scalar_t__ AV_PIX_FMT_VAAPI_VLD ; 
 scalar_t__ AV_PIX_FMT_VDA_VLD ; 
 TYPE_1__* av_hwaccel_next (TYPE_1__*) ; 

AVHWAccel *find_hwaccel_codec(AVCodecContext *codec_context)
{
	AVHWAccel *hwaccel = NULL;

	while ((hwaccel = av_hwaccel_next(hwaccel)) != NULL) {
		if (hwaccel->id == codec_context->codec_id &&
		    (hwaccel->pix_fmt == AV_PIX_FMT_VDA_VLD ||
		     hwaccel->pix_fmt == AV_PIX_FMT_DXVA2_VLD ||
		     hwaccel->pix_fmt == AV_PIX_FMT_VAAPI_VLD)) {
			return hwaccel;
		}
	}

	return NULL;
}