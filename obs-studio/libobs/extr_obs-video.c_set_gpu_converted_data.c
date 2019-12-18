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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct video_output_info {int width; int height; int format; } ;
struct video_frame {int /*<<< orphan*/ * data; int /*<<< orphan*/ * linesize; } ;
struct video_data {int /*<<< orphan*/  const* const* data; int /*<<< orphan*/ * linesize; } ;
struct obs_core_video {scalar_t__ using_nv12_tex; } ;

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
 int /*<<< orphan*/ * set_gpu_converted_plane (int const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_gpu_converted_data(struct obs_core_video *video,
				   struct video_frame *output,
				   const struct video_data *input,
				   const struct video_output_info *info)
{
	if (video->using_nv12_tex) {
		const uint32_t width = info->width;
		const uint32_t height = info->height;

		const uint8_t *const in_uv = set_gpu_converted_plane(
			width, height, input->linesize[0], output->linesize[0],
			input->data[0], output->data[0]);

		const uint32_t height_d2 = height / 2;
		set_gpu_converted_plane(width, height_d2, input->linesize[0],
					output->linesize[1], in_uv,
					output->data[1]);
	} else {
		switch (info->format) {
		case VIDEO_FORMAT_I420: {
			const uint32_t width = info->width;
			const uint32_t height = info->height;

			set_gpu_converted_plane(width, height,
						input->linesize[0],
						output->linesize[0],
						input->data[0],
						output->data[0]);

			const uint32_t width_d2 = width / 2;
			const uint32_t height_d2 = height / 2;

			set_gpu_converted_plane(width_d2, height_d2,
						input->linesize[1],
						output->linesize[1],
						input->data[1],
						output->data[1]);

			set_gpu_converted_plane(width_d2, height_d2,
						input->linesize[2],
						output->linesize[2],
						input->data[2],
						output->data[2]);

			break;
		}
		case VIDEO_FORMAT_NV12: {
			const uint32_t width = info->width;
			const uint32_t height = info->height;

			set_gpu_converted_plane(width, height,
						input->linesize[0],
						output->linesize[0],
						input->data[0],
						output->data[0]);

			const uint32_t height_d2 = height / 2;
			set_gpu_converted_plane(width, height_d2,
						input->linesize[1],
						output->linesize[1],
						input->data[1],
						output->data[1]);

			break;
		}
		case VIDEO_FORMAT_I444: {
			const uint32_t width = info->width;
			const uint32_t height = info->height;

			set_gpu_converted_plane(width, height,
						input->linesize[0],
						output->linesize[0],
						input->data[0],
						output->data[0]);

			set_gpu_converted_plane(width, height,
						input->linesize[1],
						output->linesize[1],
						input->data[1],
						output->data[1]);

			set_gpu_converted_plane(width, height,
						input->linesize[2],
						output->linesize[2],
						input->data[2],
						output->data[2]);

			break;
		}

		case VIDEO_FORMAT_NONE:
		case VIDEO_FORMAT_YVYU:
		case VIDEO_FORMAT_YUY2:
		case VIDEO_FORMAT_UYVY:
		case VIDEO_FORMAT_RGBA:
		case VIDEO_FORMAT_BGRA:
		case VIDEO_FORMAT_BGRX:
		case VIDEO_FORMAT_Y800:
		case VIDEO_FORMAT_BGR3:
		case VIDEO_FORMAT_I422:
		case VIDEO_FORMAT_I40A:
		case VIDEO_FORMAT_I42A:
		case VIDEO_FORMAT_YUVA:
		case VIDEO_FORMAT_AYUV:
			/* unimplemented */
			;
		}
	}
}