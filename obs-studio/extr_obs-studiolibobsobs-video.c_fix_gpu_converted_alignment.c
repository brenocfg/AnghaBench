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
struct video_data {int* linesize; int /*<<< orphan*/ * data; } ;
struct obs_core_video {scalar_t__* plane_linewidth; int /*<<< orphan*/ * plane_sizes; int /*<<< orphan*/ * plane_offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_dealign (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int make_aligned_linesize_offset (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void fix_gpu_converted_alignment(struct obs_core_video *video,
		struct video_frame *output, const struct video_data *input)
{
	uint32_t src_linesize = input->linesize[0];
	uint32_t dst_linesize = output->linesize[0] * 4;
	uint32_t src_pos      = 0;

	for (size_t i = 0; i < 3; i++) {
		if (video->plane_linewidth[i] == 0)
			break;

		src_pos = make_aligned_linesize_offset(video->plane_offsets[i],
				dst_linesize, src_linesize);

		copy_dealign(output->data[i], 0, dst_linesize,
				input->data[0], src_pos, src_linesize,
				video->plane_sizes[i]);
	}
}