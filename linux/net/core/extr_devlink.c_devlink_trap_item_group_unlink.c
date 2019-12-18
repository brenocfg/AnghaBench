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
struct devlink_trap_item {int /*<<< orphan*/  group_item; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_trap_group_item_put (struct devlink*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
devlink_trap_item_group_unlink(struct devlink *devlink,
			       struct devlink_trap_item *trap_item)
{
	devlink_trap_group_item_put(devlink, trap_item->group_item);
}