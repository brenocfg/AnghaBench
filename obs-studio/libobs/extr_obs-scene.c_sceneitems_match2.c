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
struct obs_sceneitem_order_info {scalar_t__ group; scalar_t__ item; } ;
typedef  int /*<<< orphan*/  obs_scene_t ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct obs_sceneitem_order_info*) ; 
 int /*<<< orphan*/  build_current_order_info (int /*<<< orphan*/ *,struct obs_sceneitem_order_info**,size_t*) ; 

__attribute__((used)) static bool sceneitems_match2(obs_scene_t *scene,
			      struct obs_sceneitem_order_info *items,
			      size_t size)
{
	struct obs_sceneitem_order_info *cur_items;
	size_t cur_size;

	build_current_order_info(scene, &cur_items, &cur_size);
	if (cur_size != size) {
		bfree(cur_items);
		return false;
	}

	for (size_t i = 0; i < size; i++) {
		struct obs_sceneitem_order_info *new = &items[i];
		struct obs_sceneitem_order_info *old = &cur_items[i];

		if (new->group != old->group || new->item != old->item) {
			bfree(cur_items);
			return false;
		}
	}

	bfree(cur_items);
	return true;
}