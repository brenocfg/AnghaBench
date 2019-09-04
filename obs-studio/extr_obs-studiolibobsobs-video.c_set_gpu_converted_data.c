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
struct video_output_info {size_t height; size_t width; int /*<<< orphan*/  format; } ;
struct video_frame {scalar_t__* linesize; int /*<<< orphan*/ ** data; } ;
struct video_data {int* linesize; int /*<<< orphan*/ ** data; } ;
struct obs_core_video {int output_width; scalar_t__* plane_linewidth; int* plane_offsets; scalar_t__ using_nv12_tex; } ;

/* Variables and functions */
 int /*<<< orphan*/  fix_gpu_converted_alignment (struct obs_core_video*,struct video_frame*,struct video_data const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  video_frame_copy (struct video_frame*,struct video_frame*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void set_gpu_converted_data(struct obs_core_video *video,
		struct video_frame *output, const struct video_data *input,
		const struct video_output_info *info)
{
	if (input->linesize[0] == video->output_width*4) {
		struct video_frame frame;

		for (size_t i = 0; i < 3; i++) {
			if (video->plane_linewidth[i] == 0)
				break;

			frame.linesize[i] = video->plane_linewidth[i];
			frame.data[i] =
				input->data[0] + video->plane_offsets[i];
		}

		video_frame_copy(output, &frame, info->format, info->height);

	} else if (video->using_nv12_tex) {
		size_t width = info->width;
		size_t height = info->height;
		size_t height_d2 = height / 2;
		uint8_t *out_y = output->data[0];
		uint8_t *out_uv = output->data[1];
		uint8_t *in = input->data[0];

		for (size_t y = 0; y < height; y++) {
			memcpy(out_y, in, width);
			out_y += output->linesize[0];
			in += input->linesize[0];
		}
		for (size_t y = 0; y < height_d2; y++) {
			memcpy(out_uv, in, width);
			out_uv += output->linesize[0];
			in += input->linesize[0];
		}

	} else {
		fix_gpu_converted_alignment(video, output, input);
	}
}