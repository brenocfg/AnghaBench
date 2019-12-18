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
struct video_output_info {int height; int width; } ;
struct video_frame {int* linesize; int /*<<< orphan*/ ** data; } ;
struct video_data {int* linesize; int /*<<< orphan*/ ** data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void copy_rgbx_frame(struct video_frame *output,
				   const struct video_data *input,
				   const struct video_output_info *info)
{
	uint8_t *in_ptr = input->data[0];
	uint8_t *out_ptr = output->data[0];

	/* if the line sizes match, do a single copy */
	if (input->linesize[0] == output->linesize[0]) {
		memcpy(out_ptr, in_ptr, input->linesize[0] * info->height);
	} else {
		for (size_t y = 0; y < info->height; y++) {
			memcpy(out_ptr, in_ptr, info->width * 4);
			in_ptr += input->linesize[0];
			out_ptr += output->linesize[0];
		}
	}
}