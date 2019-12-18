#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct video_frame {int* linesize; int /*<<< orphan*/ * data; } ;
typedef  enum video_format { ____Placeholder_video_format } video_format ;

/* Variables and functions */
#define  VIDEO_FORMAT_AYUV 144 
#define  VIDEO_FORMAT_BGR3 143 
#define  VIDEO_FORMAT_BGRA 142 
#define  VIDEO_FORMAT_BGRX 141 
#define  VIDEO_FORMAT_I40A 140 
#define  VIDEO_FORMAT_I420 139 
#define  VIDEO_FORMAT_I422 138 
#define  VIDEO_FORMAT_I42A 137 
#define  VIDEO_FORMAT_I444 136 
#define  VIDEO_FORMAT_NONE 135 
#define  VIDEO_FORMAT_NV12 134 
#define  VIDEO_FORMAT_RGBA 133 
#define  VIDEO_FORMAT_UYVY 132 
#define  VIDEO_FORMAT_Y800 131 
#define  VIDEO_FORMAT_YUVA 130 
#define  VIDEO_FORMAT_YUY2 129 
#define  VIDEO_FORMAT_YVYU 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void video_frame_copy(struct video_frame *dst, const struct video_frame *src,
		      enum video_format format, uint32_t cy)
{
	switch (format) {
	case VIDEO_FORMAT_NONE:
		return;

	case VIDEO_FORMAT_I420:
		memcpy(dst->data[0], src->data[0], src->linesize[0] * cy);
		memcpy(dst->data[1], src->data[1], src->linesize[1] * cy / 2);
		memcpy(dst->data[2], src->data[2], src->linesize[2] * cy / 2);
		break;

	case VIDEO_FORMAT_NV12:
		memcpy(dst->data[0], src->data[0], src->linesize[0] * cy);
		memcpy(dst->data[1], src->data[1], src->linesize[1] * cy / 2);
		break;

	case VIDEO_FORMAT_Y800:
	case VIDEO_FORMAT_YVYU:
	case VIDEO_FORMAT_YUY2:
	case VIDEO_FORMAT_UYVY:
	case VIDEO_FORMAT_RGBA:
	case VIDEO_FORMAT_BGRA:
	case VIDEO_FORMAT_BGRX:
	case VIDEO_FORMAT_BGR3:
	case VIDEO_FORMAT_AYUV:
		memcpy(dst->data[0], src->data[0], src->linesize[0] * cy);
		break;

	case VIDEO_FORMAT_I444:
	case VIDEO_FORMAT_I422:
		memcpy(dst->data[0], src->data[0], src->linesize[0] * cy);
		memcpy(dst->data[1], src->data[1], src->linesize[1] * cy);
		memcpy(dst->data[2], src->data[2], src->linesize[2] * cy);
		break;

	case VIDEO_FORMAT_I40A:
		memcpy(dst->data[0], src->data[0], src->linesize[0] * cy);
		memcpy(dst->data[1], src->data[1], src->linesize[1] * cy / 2);
		memcpy(dst->data[2], src->data[2], src->linesize[2] * cy / 2);
		memcpy(dst->data[3], src->data[3], src->linesize[3] * cy);
		break;

	case VIDEO_FORMAT_I42A:
	case VIDEO_FORMAT_YUVA:
		memcpy(dst->data[0], src->data[0], src->linesize[0] * cy);
		memcpy(dst->data[1], src->data[1], src->linesize[1] * cy);
		memcpy(dst->data[2], src->data[2], src->linesize[2] * cy);
		memcpy(dst->data[3], src->data[3], src->linesize[3] * cy);
		break;
	}
}