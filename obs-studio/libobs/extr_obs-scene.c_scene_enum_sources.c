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
struct obs_scene_item {int /*<<< orphan*/  source; int /*<<< orphan*/  active_refs; struct obs_scene_item* next; } ;
struct obs_scene {int /*<<< orphan*/  source; struct obs_scene_item* first_item; } ;
typedef  int /*<<< orphan*/  (* obs_source_enum_proc_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  full_lock (struct obs_scene*) ; 
 int /*<<< orphan*/  full_unlock (struct obs_scene*) ; 
 int /*<<< orphan*/  obs_sceneitem_addref (struct obs_scene_item*) ; 
 int /*<<< orphan*/  obs_sceneitem_release (struct obs_scene_item*) ; 
 scalar_t__ os_atomic_load_long (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scene_enum_sources(void *data, obs_source_enum_proc_t enum_callback,
			       void *param, bool active)
{
	struct obs_scene *scene = data;
	struct obs_scene_item *item;
	struct obs_scene_item *next;

	full_lock(scene);
	item = scene->first_item;

	while (item) {
		next = item->next;

		obs_sceneitem_addref(item);
		if (!active || os_atomic_load_long(&item->active_refs) > 0)
			enum_callback(scene->source, item->source, param);
		obs_sceneitem_release(item);

		item = next;
	}

	full_unlock(scene);
}