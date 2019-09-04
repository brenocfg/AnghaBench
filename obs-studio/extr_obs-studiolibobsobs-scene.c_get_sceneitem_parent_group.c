#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ parent; struct TYPE_10__* next; TYPE_2__* source; scalar_t__ is_group; } ;
typedef  TYPE_3__ obs_sceneitem_t ;
struct TYPE_11__ {TYPE_3__* first_item; } ;
typedef  TYPE_4__ obs_scene_t ;
struct TYPE_8__ {scalar_t__ data; } ;
struct TYPE_9__ {TYPE_1__ context; } ;

/* Variables and functions */

__attribute__((used)) static obs_sceneitem_t *get_sceneitem_parent_group(obs_scene_t *scene,
		obs_sceneitem_t *group_subitem)
{
	if (group_subitem->is_group)
		return NULL;

	obs_sceneitem_t *item = scene->first_item;
	while (item) {
		if (item->is_group &&
		    item->source->context.data == group_subitem->parent)
			return item;
		item = item->next;
	}

	return NULL;
}