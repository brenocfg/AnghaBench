#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ obs_sceneitem_t ;
struct TYPE_6__ {TYPE_1__* first_item; } ;
typedef  TYPE_2__ obs_scene_t ;

/* Variables and functions */

__attribute__((used)) static bool sceneitems_match(obs_scene_t *scene, obs_sceneitem_t * const *items,
		size_t size, bool *order_matches)
{
	obs_sceneitem_t *item = scene->first_item;

	size_t count = 0;
	while (item) {
		bool found = false;
		for (size_t i = 0; i < size; i++) {
			if (items[i] != item)
				continue;

			if (count != i)
				*order_matches = false;

			found = true;
			break;
		}

		if (!found)
			return false;

		item = item->next;
		count += 1;
	}

	return count == size;
}