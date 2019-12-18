#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct obs_transform_info {int /*<<< orphan*/  bounds; int /*<<< orphan*/  bounds_alignment; int /*<<< orphan*/  bounds_type; int /*<<< orphan*/  alignment; int /*<<< orphan*/  scale; int /*<<< orphan*/  rot; int /*<<< orphan*/  pos; } ;
struct TYPE_4__ {int /*<<< orphan*/  bounds; int /*<<< orphan*/  bounds_align; int /*<<< orphan*/  bounds_type; int /*<<< orphan*/  align; int /*<<< orphan*/  scale; int /*<<< orphan*/  rot; int /*<<< orphan*/  pos; } ;
typedef  TYPE_1__ obs_sceneitem_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_update_transform (TYPE_1__*) ; 

void obs_sceneitem_set_info(obs_sceneitem_t *item,
			    const struct obs_transform_info *info)
{
	if (item && info) {
		item->pos = info->pos;
		item->rot = info->rot;
		item->scale = info->scale;
		item->align = info->alignment;
		item->bounds_type = info->bounds_type;
		item->bounds_align = info->bounds_alignment;
		item->bounds = info->bounds;
		do_update_transform(item);
	}
}