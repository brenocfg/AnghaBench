#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  defer_update; } ;
typedef  TYPE_1__ obs_sceneitem_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_update_transform (TYPE_1__*) ; 
 int /*<<< orphan*/  obs_ptr_valid (TYPE_1__*,char*) ; 
 scalar_t__ os_atomic_dec_long (int /*<<< orphan*/ *) ; 

void obs_sceneitem_defer_update_end(obs_sceneitem_t *item)
{
	if (!obs_ptr_valid(item, "obs_sceneitem_defer_update_end"))
		return;

	if (os_atomic_dec_long(&item->defer_update) == 0)
		do_update_transform(item);
}