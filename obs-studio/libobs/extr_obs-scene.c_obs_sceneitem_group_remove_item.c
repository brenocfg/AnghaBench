#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* parent; struct TYPE_11__* next; struct TYPE_11__* prev; int /*<<< orphan*/  is_group; } ;
typedef  TYPE_1__ obs_sceneitem_t ;
struct TYPE_12__ {TYPE_1__* first_item; } ;
typedef  TYPE_2__ obs_scene_t ;

/* Variables and functions */
 int /*<<< orphan*/  detach_sceneitem (TYPE_1__*) ; 
 int /*<<< orphan*/  full_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  full_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  remove_group_transform (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  resize_group (TYPE_1__*) ; 

void obs_sceneitem_group_remove_item(obs_sceneitem_t *group,
				     obs_sceneitem_t *item)
{
	if (!item || !group || !group->is_group)
		return;

	obs_scene_t *groupscene = item->parent;
	obs_scene_t *scene = group->parent;

	/* ------------------------- */

	full_lock(scene);
	full_lock(groupscene);
	remove_group_transform(group, item);
	detach_sceneitem(item);

	/* ------------------------- */

	if (group->prev) {
		group->prev->next = item;
		item->prev = group->prev;
	} else {
		scene->first_item = item;
		item->prev = NULL;
	}
	group->prev = item;
	item->next = group;
	item->parent = scene;

	/* ------------------------- */

	resize_group(group);
	full_unlock(groupscene);
	full_unlock(scene);
}