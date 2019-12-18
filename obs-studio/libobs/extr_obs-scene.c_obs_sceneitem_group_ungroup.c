#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {struct TYPE_21__* next; TYPE_10__* source; TYPE_3__* parent; int /*<<< orphan*/  is_group; } ;
typedef  TYPE_2__ obs_sceneitem_t ;
struct TYPE_22__ {TYPE_2__* first_item; } ;
typedef  TYPE_3__ obs_scene_t ;
struct TYPE_20__ {TYPE_3__* data; } ;
struct TYPE_19__ {TYPE_1__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  apply_group_transform (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  detach_sceneitem (TYPE_2__*) ; 
 int /*<<< orphan*/  duplicate_item_data (TYPE_2__*,TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  full_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  full_unlock (TYPE_3__*) ; 
 TYPE_2__* obs_scene_add_internal (TYPE_3__*,TYPE_10__*,TYPE_2__*) ; 
 int /*<<< orphan*/  obs_sceneitem_release (TYPE_2__*) ; 
 int /*<<< orphan*/  remove_group_transform (TYPE_2__*,TYPE_2__*) ; 

void obs_sceneitem_group_ungroup(obs_sceneitem_t *item)
{
	if (!item || !item->is_group)
		return;

	obs_scene_t *scene = item->parent;
	obs_scene_t *subscene = item->source->context.data;
	obs_sceneitem_t *insert_after = item;
	obs_sceneitem_t *first;
	obs_sceneitem_t *last;

	full_lock(scene);

	/* ------------------------- */

	full_lock(subscene);
	first = subscene->first_item;
	last = first;
	while (last) {
		obs_sceneitem_t *dst;

		remove_group_transform(item, last);
		dst = obs_scene_add_internal(scene, last->source, insert_after);
		duplicate_item_data(dst, last, true, true, true);
		apply_group_transform(last, item);

		if (!last->next)
			break;

		insert_after = dst;
		last = last->next;
	}
	full_unlock(subscene);

	/* ------------------------- */

	detach_sceneitem(item);
	full_unlock(scene);

	obs_sceneitem_release(item);
}