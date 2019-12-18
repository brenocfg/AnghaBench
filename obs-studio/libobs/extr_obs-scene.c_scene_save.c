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
struct obs_scene_item {struct obs_scene_item* next; } ;
struct obs_scene {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; scalar_t__ custom_size; int /*<<< orphan*/  id_counter; struct obs_scene_item* first_item; } ;
typedef  int /*<<< orphan*/  obs_data_t ;
typedef  int /*<<< orphan*/  obs_data_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  full_lock (struct obs_scene*) ; 
 int /*<<< orphan*/  full_unlock (struct obs_scene*) ; 
 int /*<<< orphan*/ * obs_data_array_create () ; 
 int /*<<< orphan*/  obs_data_array_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_set_array (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_data_set_bool (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  obs_data_set_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scene_save_item (int /*<<< orphan*/ *,struct obs_scene_item*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scene_save(void *data, obs_data_t *settings)
{
	struct obs_scene *scene = data;
	obs_data_array_t *array = obs_data_array_create();
	struct obs_scene_item *item;

	full_lock(scene);

	item = scene->first_item;
	while (item) {
		scene_save_item(array, item, NULL);
		item = item->next;
	}

	obs_data_set_int(settings, "id_counter", scene->id_counter);
	obs_data_set_bool(settings, "custom_size", scene->custom_size);
	if (scene->custom_size) {
		obs_data_set_int(settings, "cx", scene->cx);
		obs_data_set_int(settings, "cy", scene->cy);
	}

	full_unlock(scene);

	obs_data_set_array(settings, "items", array);
	obs_data_array_release(array);
}