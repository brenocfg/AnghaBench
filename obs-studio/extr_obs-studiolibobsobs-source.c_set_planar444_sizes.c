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
struct obs_source_frame {int height; scalar_t__* data; int /*<<< orphan*/  width; } ;
struct obs_source {int async_convert_height; int* async_plane_offset; int /*<<< orphan*/  async_texture_format; int /*<<< orphan*/  async_convert_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_R8 ; 

__attribute__((used)) static inline bool set_planar444_sizes(struct obs_source *source,
	const struct obs_source_frame *frame)
{
	source->async_convert_width   = frame->width;
	source->async_convert_height  = frame->height * 3;
	source->async_texture_format  = GS_R8;
	source->async_plane_offset[0] = (int)(frame->data[1] - frame->data[0]);
	source->async_plane_offset[1] = (int)(frame->data[2] - frame->data[0]);
	return true;
}