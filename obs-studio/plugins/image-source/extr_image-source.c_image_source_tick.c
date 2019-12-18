#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  scalar_t__ time_t ;
struct TYPE_4__ {scalar_t__ is_animated_gif; scalar_t__ cur_time; scalar_t__ cur_loop; scalar_t__ cur_frame; } ;
struct TYPE_5__ {TYPE_1__ image; } ;
struct image_source {float update_time_elapsed; scalar_t__ file_timestamp; int active; void* last_time; TYPE_2__ if2; int /*<<< orphan*/  source; int /*<<< orphan*/  file; } ;

/* Variables and functions */
 scalar_t__ get_modified_timestamp (int /*<<< orphan*/ ) ; 
 int gs_image_file2_tick (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  gs_image_file2_update_texture (TYPE_2__*) ; 
 int /*<<< orphan*/  image_source_load (struct image_source*) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 void* obs_get_video_frame_time () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 
 scalar_t__ obs_source_active (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void image_source_tick(void *data, float seconds)
{
	struct image_source *context = data;
	uint64_t frame_time = obs_get_video_frame_time();

	context->update_time_elapsed += seconds;

	if (context->update_time_elapsed >= 1.0f) {
		time_t t = get_modified_timestamp(context->file);
		context->update_time_elapsed = 0.0f;

		if (context->file_timestamp != t) {
			image_source_load(context);
		}
	}

	if (obs_source_active(context->source)) {
		if (!context->active) {
			if (context->if2.image.is_animated_gif)
				context->last_time = frame_time;
			context->active = true;
		}

	} else {
		if (context->active) {
			if (context->if2.image.is_animated_gif) {
				context->if2.image.cur_frame = 0;
				context->if2.image.cur_loop = 0;
				context->if2.image.cur_time = 0;

				obs_enter_graphics();
				gs_image_file2_update_texture(&context->if2);
				obs_leave_graphics();
			}

			context->active = false;
		}

		return;
	}

	if (context->last_time && context->if2.image.is_animated_gif) {
		uint64_t elapsed = frame_time - context->last_time;
		bool updated = gs_image_file2_tick(&context->if2, elapsed);

		if (updated) {
			obs_enter_graphics();
			gs_image_file2_update_texture(&context->if2);
			obs_leave_graphics();
		}
	}

	context->last_time = frame_time;
}