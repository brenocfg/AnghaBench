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
struct TYPE_4__ {int /*<<< orphan*/  update_transform; } ;
typedef  TYPE_1__ obs_sceneitem_t ;

/* Variables and functions */
 scalar_t__ os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  update_item_transform (TYPE_1__*,int) ; 

void obs_sceneitem_force_update_transform(obs_sceneitem_t *item)
{
	if (!item)
		return;

	if (os_atomic_set_bool(&item->update_transform, false))
		update_item_transform(item, false);
}