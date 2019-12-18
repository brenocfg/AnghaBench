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
struct obs_scene_item {struct obs_scene_item* next; struct obs_scene_item* prev; } ;
struct obs_scene {int dummy; } ;
struct TYPE_6__ {struct obs_scene_item* prev; struct obs_scene_item* next; struct obs_scene* parent; } ;
typedef  TYPE_1__ obs_sceneitem_t ;
typedef  enum obs_order_movement { ____Placeholder_obs_order_movement } obs_order_movement ;

/* Variables and functions */
 int OBS_ORDER_MOVE_BOTTOM ; 
 int OBS_ORDER_MOVE_DOWN ; 
 int OBS_ORDER_MOVE_TOP ; 
 int OBS_ORDER_MOVE_UP ; 
 int /*<<< orphan*/  attach_sceneitem (struct obs_scene*,TYPE_1__*,struct obs_scene_item*) ; 
 int /*<<< orphan*/  detach_sceneitem (TYPE_1__*) ; 
 int /*<<< orphan*/  full_lock (struct obs_scene*) ; 
 int /*<<< orphan*/  full_unlock (struct obs_scene*) ; 
 int /*<<< orphan*/  obs_scene_addref (struct obs_scene*) ; 
 int /*<<< orphan*/  obs_scene_release (struct obs_scene*) ; 
 int /*<<< orphan*/  signal_reorder (TYPE_1__*) ; 

void obs_sceneitem_set_order(obs_sceneitem_t *item,
			     enum obs_order_movement movement)
{
	if (!item)
		return;

	struct obs_scene_item *next, *prev;
	struct obs_scene *scene = item->parent;

	obs_scene_addref(scene);
	full_lock(scene);

	next = item->next;
	prev = item->prev;

	detach_sceneitem(item);

	if (movement == OBS_ORDER_MOVE_DOWN) {
		attach_sceneitem(scene, item, prev ? prev->prev : NULL);

	} else if (movement == OBS_ORDER_MOVE_UP) {
		attach_sceneitem(scene, item, next ? next : prev);

	} else if (movement == OBS_ORDER_MOVE_TOP) {
		struct obs_scene_item *last = next;
		if (!last) {
			last = prev;
		} else {
			while (last->next)
				last = last->next;
		}

		attach_sceneitem(scene, item, last);

	} else if (movement == OBS_ORDER_MOVE_BOTTOM) {
		attach_sceneitem(scene, item, NULL);
	}

	full_unlock(scene);

	signal_reorder(item);
	obs_scene_release(scene);
}