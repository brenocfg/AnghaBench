#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  scalar_t__ time_t ;
struct TYPE_3__ {scalar_t__ is_animated_gif; } ;
struct mask_filter_data {float update_time_elapsed; scalar_t__ image_file_timestamp; void* last_time; TYPE_1__ image; int /*<<< orphan*/  image_file; } ;

/* Variables and functions */
 scalar_t__ get_modified_timestamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_image_file_tick (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  gs_image_file_update_texture (TYPE_1__*) ; 
 int /*<<< orphan*/  mask_filter_image_load (struct mask_filter_data*) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 void* obs_get_video_frame_time () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 

__attribute__((used)) static void mask_filter_tick(void *data, float seconds)
{
	struct mask_filter_data *filter = data;
	filter->update_time_elapsed += seconds;

	if (filter->update_time_elapsed >= 1.0f) {
		time_t t = get_modified_timestamp(filter->image_file);
		filter->update_time_elapsed = 0.0f;

		if (filter->image_file_timestamp != t) {
			mask_filter_image_load(filter);
		}
	}

	if (filter->image.is_animated_gif) {
		uint64_t cur_time = obs_get_video_frame_time();

		if (!filter->last_time)
			filter->last_time = cur_time;

		gs_image_file_tick(&filter->image,
				   cur_time - filter->last_time);
		obs_enter_graphics();
		gs_image_file_update_texture(&filter->image);
		obs_leave_graphics();

		filter->last_time = cur_time;
	}
}