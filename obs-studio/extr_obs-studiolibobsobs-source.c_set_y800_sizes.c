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
struct obs_source {int /*<<< orphan*/  async_texture_format; int /*<<< orphan*/  async_convert_height; int /*<<< orphan*/  async_convert_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_R8 ; 

__attribute__((used)) static inline bool set_y800_sizes(struct obs_source *source,
	const struct obs_source_frame *frame)
{
	source->async_convert_width   = frame->width;
	source->async_convert_height  = frame->height;
	source->async_texture_format  = GS_R8;
	return true;
}