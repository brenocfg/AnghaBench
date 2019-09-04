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
struct obs_source_frame {int width; int height; scalar_t__* data; } ;
struct obs_source {int async_convert_width; int async_convert_height; int* async_plane_offset; int /*<<< orphan*/  async_texture_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_R8 ; 

__attribute__((used)) static inline bool set_planar420_sizes(struct obs_source *source,
		const struct obs_source_frame *frame)
{
	uint32_t size = frame->width * frame->height;
	size += size/2;

	source->async_convert_width   = frame->width;
	source->async_convert_height  = size / frame->width;
	source->async_texture_format  = GS_R8;
	source->async_plane_offset[0] = (int)(frame->data[1] - frame->data[0]);
	source->async_plane_offset[1] = (int)(frame->data[2] - frame->data[0]);
	return true;
}