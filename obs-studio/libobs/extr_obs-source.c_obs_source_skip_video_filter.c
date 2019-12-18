#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_15__ {int output_flags; scalar_t__ video_render; } ;
struct TYPE_16__ {TYPE_1__ info; } ;
typedef  TYPE_2__ obs_source_t ;

/* Variables and functions */
 int OBS_SOURCE_ASYNC ; 
 int OBS_SOURCE_CUSTOM_DRAW ; 
 int /*<<< orphan*/  deinterlace_render (TYPE_2__*) ; 
 scalar_t__ deinterlacing_enabled (TYPE_2__*) ; 
 TYPE_2__* obs_filter_get_parent (TYPE_2__*) ; 
 TYPE_2__* obs_filter_get_target (TYPE_2__*) ; 
 int /*<<< orphan*/  obs_ptr_valid (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  obs_source_default_render (TYPE_2__*) ; 
 int /*<<< orphan*/  obs_source_main_render (TYPE_2__*) ; 
 int /*<<< orphan*/  obs_source_render_async_video (TYPE_2__*) ; 
 int /*<<< orphan*/  obs_source_video_render (TYPE_2__*) ; 

void obs_source_skip_video_filter(obs_source_t *filter)
{
	obs_source_t *target, *parent;
	bool custom_draw, async;
	uint32_t parent_flags;

	if (!obs_ptr_valid(filter, "obs_source_skip_video_filter"))
		return;

	target = obs_filter_get_target(filter);
	parent = obs_filter_get_parent(filter);
	parent_flags = parent->info.output_flags;
	custom_draw = (parent_flags & OBS_SOURCE_CUSTOM_DRAW) != 0;
	async = (parent_flags & OBS_SOURCE_ASYNC) != 0;

	if (target == parent) {
		if (!custom_draw && !async)
			obs_source_default_render(target);
		else if (target->info.video_render)
			obs_source_main_render(target);
		else if (deinterlacing_enabled(target))
			deinterlace_render(target);
		else
			obs_source_render_async_video(target);

	} else {
		obs_source_video_render(target);
	}
}