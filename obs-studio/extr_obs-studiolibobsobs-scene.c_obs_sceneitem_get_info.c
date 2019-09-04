#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct obs_transform_info {int /*<<< orphan*/  bounds; int /*<<< orphan*/  bounds_alignment; int /*<<< orphan*/  bounds_type; int /*<<< orphan*/  alignment; int /*<<< orphan*/  scale; int /*<<< orphan*/  rot; int /*<<< orphan*/  pos; } ;
struct TYPE_3__ {int /*<<< orphan*/  bounds; int /*<<< orphan*/  bounds_align; int /*<<< orphan*/  bounds_type; int /*<<< orphan*/  align; int /*<<< orphan*/  scale; int /*<<< orphan*/  rot; int /*<<< orphan*/  pos; } ;
typedef  TYPE_1__ obs_sceneitem_t ;

/* Variables and functions */

void obs_sceneitem_get_info(const obs_sceneitem_t *item,
		struct obs_transform_info *info)
{
	if (item && info) {
		info->pos              = item->pos;
		info->rot              = item->rot;
		info->scale            = item->scale;
		info->alignment        = item->align;
		info->bounds_type      = item->bounds_type;
		info->bounds_alignment = item->bounds_align;
		info->bounds           = item->bounds;
	}
}