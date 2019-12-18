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
typedef  void* uint32_t ;
struct obs_scene {int custom_size; void* cy; void* cx; scalar_t__ id_counter; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  obs_data_array_t ;

/* Variables and functions */
 size_t obs_data_array_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_data_array_item (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  obs_data_array_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_data_get_array (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_get_bool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_get_int (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_data_has_user_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obs_data_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_all_items (struct obs_scene*) ; 
 int /*<<< orphan*/  scene_load_item (struct obs_scene*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scene_load(void *data, obs_data_t *settings)
{
	struct obs_scene *scene = data;
	obs_data_array_t *items = obs_data_get_array(settings, "items");
	size_t count, i;

	remove_all_items(scene);

	if (!items)
		return;

	count = obs_data_array_count(items);

	for (i = 0; i < count; i++) {
		obs_data_t *item_data = obs_data_array_item(items, i);
		scene_load_item(scene, item_data);
		obs_data_release(item_data);
	}

	if (obs_data_has_user_value(settings, "id_counter"))
		scene->id_counter = obs_data_get_int(settings, "id_counter");

	if (obs_data_get_bool(settings, "custom_size")) {
		scene->cx = (uint32_t)obs_data_get_int(settings, "cx");
		scene->cy = (uint32_t)obs_data_get_int(settings, "cy");
		scene->custom_size = true;
	}

	obs_data_array_release(items);
}