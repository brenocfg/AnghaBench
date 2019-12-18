#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct obs_scene_item {struct obs_scene_item* next; } ;
struct obs_scene {struct obs_scene_item* first_item; } ;
struct TYPE_6__ {struct obs_scene* parent; } ;
typedef  TYPE_1__ obs_sceneitem_t ;

/* Variables and functions */
 int /*<<< orphan*/  attach_sceneitem (struct obs_scene*,TYPE_1__*,struct obs_scene_item*) ; 
 int /*<<< orphan*/  detach_sceneitem (TYPE_1__*) ; 
 int /*<<< orphan*/  full_lock (struct obs_scene*) ; 
 int /*<<< orphan*/  full_unlock (struct obs_scene*) ; 
 int /*<<< orphan*/  obs_scene_addref (struct obs_scene*) ; 
 int /*<<< orphan*/  obs_scene_release (struct obs_scene*) ; 
 int /*<<< orphan*/  signal_reorder (TYPE_1__*) ; 

void obs_sceneitem_set_order_position(obs_sceneitem_t *item, int position)
{
	if (!item)
		return;

	struct obs_scene *scene = item->parent;
	struct obs_scene_item *next;

	obs_scene_addref(scene);
	full_lock(scene);

	detach_sceneitem(item);
	next = scene->first_item;

	if (position == 0) {
		attach_sceneitem(scene, item, NULL);
	} else {
		for (int i = position; i > 1; --i) {
			if (next->next == NULL)
				break;
			next = next->next;
		}

		attach_sceneitem(scene, item, next);
	}

	full_unlock(scene);

	signal_reorder(item);
	obs_scene_release(scene);
}