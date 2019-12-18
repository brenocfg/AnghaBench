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
struct TYPE_6__ {int /*<<< orphan*/  rot; int /*<<< orphan*/  scale; int /*<<< orphan*/  pos; int /*<<< orphan*/ * parent; } ;
typedef  TYPE_1__ obs_sceneitem_t ;
typedef  int /*<<< orphan*/  obs_scene_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_ungrouped_transform (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_item_transform (TYPE_1__*,int) ; 

__attribute__((used)) static void remove_group_transform(obs_sceneitem_t *group,
				   obs_sceneitem_t *item)
{
	obs_scene_t *parent = item->parent;
	if (!parent || !group)
		return;

	get_ungrouped_transform(group, &item->pos, &item->scale, &item->rot);

	update_item_transform(item, false);
}