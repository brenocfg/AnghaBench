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
struct obs_source_frame {int format; int height; int /*<<< orphan*/  color_range_max; int /*<<< orphan*/  color_range_min; int /*<<< orphan*/  full_range; int /*<<< orphan*/  color_matrix; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  flip; } ;

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
 int /*<<< orphan*/  copy_frame_data_plane (struct obs_source_frame*,struct obs_source_frame const*,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static void copy_frame_data(struct obs_source_frame *dst,
			    const struct obs_source_frame *src)
{
	dst->flip = src->flip;
	dst->full_range = src->full_range;
	dst->timestamp = src->timestamp;
	memcpy(dst->color_matrix, src->color_matrix, sizeof(float) * 16);
	if (!dst->full_range) {
		size_t const size = sizeof(float) * 3;
		memcpy(dst->color_range_min, src->color_range_min, size);
		memcpy(dst->color_range_max, src->color_range_max, size);
	}

	switch (src->format) {
	case VIDEO_FORMAT_I420:
		copy_frame_data_plane(dst, src, 0, dst->height);
		copy_frame_data_plane(dst, src, 1, dst->height / 2);
		copy_frame_data_plane(dst, src, 2, dst->height / 2);
		break;

	case VIDEO_FORMAT_NV12:
		copy_frame_data_plane(dst, src, 0, dst->height);
		copy_frame_data_plane(dst, src, 1, dst->height / 2);
		break;

	case VIDEO_FORMAT_I444:
	case VIDEO_FORMAT_I422:
		copy_frame_data_plane(dst, src, 0, dst->height);
		copy_frame_data_plane(dst, src, 1, dst->height);
		copy_frame_data_plane(dst, src, 2, dst->height);
		break;

	case VIDEO_FORMAT_YVYU:
	case VIDEO_FORMAT_YUY2:
	case VIDEO_FORMAT_UYVY:
	case VIDEO_FORMAT_NONE:
	case VIDEO_FORMAT_RGBA:
	case VIDEO_FORMAT_BGRA:
	case VIDEO_FORMAT_BGRX:
	case VIDEO_FORMAT_Y800:
	case VIDEO_FORMAT_BGR3:
	case VIDEO_FORMAT_AYUV:
		copy_frame_data_plane(dst, src, 0, dst->height);
		break;

	case VIDEO_FORMAT_I40A:
		copy_frame_data_plane(dst, src, 0, dst->height);
		copy_frame_data_plane(dst, src, 1, dst->height / 2);
		copy_frame_data_plane(dst, src, 2, dst->height / 2);
		copy_frame_data_plane(dst, src, 3, dst->height);
		break;

	case VIDEO_FORMAT_I42A:
	case VIDEO_FORMAT_YUVA:
		copy_frame_data_plane(dst, src, 0, dst->height);
		copy_frame_data_plane(dst, src, 1, dst->height);
		copy_frame_data_plane(dst, src, 2, dst->height);
		copy_frame_data_plane(dst, src, 3, dst->height);
		break;
	}
}