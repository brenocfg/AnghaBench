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
struct TYPE_3__ {int /*<<< orphan*/  texture; } ;
struct mask_filter_data {char* image_file; TYPE_1__ image; int /*<<< orphan*/  target; scalar_t__ update_time_elapsed; int /*<<< orphan*/  image_file_timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_modified_timestamp (char*) ; 
 int /*<<< orphan*/  gs_image_file_init (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  gs_image_file_init_texture (TYPE_1__*) ; 
 int /*<<< orphan*/  mask_filter_image_unload (struct mask_filter_data*) ; 
 int /*<<< orphan*/  obs_enter_graphics () ; 
 int /*<<< orphan*/  obs_leave_graphics () ; 

__attribute__((used)) static void mask_filter_image_load(struct mask_filter_data *filter)
{
	mask_filter_image_unload(filter);

	char *path = filter->image_file;

	if (path && *path) {
		filter->image_file_timestamp = get_modified_timestamp(path);
		gs_image_file_init(&filter->image, path);
		filter->update_time_elapsed = 0;

		obs_enter_graphics();
		gs_image_file_init_texture(&filter->image);
		obs_leave_graphics();

		filter->target = filter->image.texture;
	}
}