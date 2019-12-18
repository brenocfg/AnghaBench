#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct obs_scene_item {scalar_t__ id; struct obs_scene_item* next; } ;
typedef  struct obs_scene_item obs_sceneitem_t ;
struct TYPE_5__ {struct obs_scene_item* first_item; } ;
typedef  TYPE_1__ obs_scene_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  full_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  full_unlock (TYPE_1__*) ; 

obs_sceneitem_t *obs_scene_find_sceneitem_by_id(obs_scene_t *scene, int64_t id)
{
	struct obs_scene_item *item;

	if (!scene)
		return NULL;

	full_lock(scene);

	item = scene->first_item;
	while (item) {
		if (item->id == id)
			break;

		item = item->next;
	}

	full_unlock(scene);

	return item;
}