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
struct devlink_trap_group_item {int /*<<< orphan*/  refcount; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_trap_group_item_destroy (struct devlink*,struct devlink_trap_group_item*) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
devlink_trap_group_item_put(struct devlink *devlink,
			    struct devlink_trap_group_item *group_item)
{
	if (!refcount_dec_and_test(&group_item->refcount))
		return;

	devlink_trap_group_item_destroy(devlink, group_item);
}