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
struct obs_source_frame {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct obs_source {int async_channel_count; void** async_texture_formats; int /*<<< orphan*/ * async_convert_height; int /*<<< orphan*/ * async_convert_width; } ;

/* Variables and functions */
 void* GS_R8 ; 

__attribute__((used)) static inline bool
set_planar444_alpha_sizes(struct obs_source *source,
			  const struct obs_source_frame *frame)
{
	source->async_convert_width[0] = frame->width;
	source->async_convert_width[1] = frame->width;
	source->async_convert_width[2] = frame->width;
	source->async_convert_width[3] = frame->width;
	source->async_convert_height[0] = frame->height;
	source->async_convert_height[1] = frame->height;
	source->async_convert_height[2] = frame->height;
	source->async_convert_height[3] = frame->height;
	source->async_texture_formats[0] = GS_R8;
	source->async_texture_formats[1] = GS_R8;
	source->async_texture_formats[2] = GS_R8;
	source->async_texture_formats[3] = GS_R8;
	source->async_channel_count = 4;
	return true;
}