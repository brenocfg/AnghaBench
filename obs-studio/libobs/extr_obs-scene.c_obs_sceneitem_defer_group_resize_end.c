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
struct TYPE_4__ {int /*<<< orphan*/  update_group_resize; int /*<<< orphan*/  defer_group_resize; } ;
typedef  TYPE_1__ obs_sceneitem_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_ptr_valid (TYPE_1__*,char*) ; 
 scalar_t__ os_atomic_dec_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 

void obs_sceneitem_defer_group_resize_end(obs_sceneitem_t *item)
{
	if (!obs_ptr_valid(item, "obs_sceneitem_defer_group_resize_end"))
		return;

	if (os_atomic_dec_long(&item->defer_group_resize) == 0)
		os_atomic_set_bool(&item->update_group_resize, true);
}