#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct devlink_trap_item {int /*<<< orphan*/  stats; int /*<<< orphan*/  list; } ;
struct devlink_trap {int /*<<< orphan*/  name; } ;
struct devlink {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* trap_fini ) (struct devlink*,struct devlink_trap const*,struct devlink_trap_item*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_CMD_TRAP_DEL ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  devlink_trap_item_group_unlink (struct devlink*,struct devlink_trap_item*) ; 
 struct devlink_trap_item* devlink_trap_item_lookup (struct devlink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_trap_notify (struct devlink*,struct devlink_trap_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct devlink_trap_item*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct devlink*,struct devlink_trap const*,struct devlink_trap_item*) ; 

__attribute__((used)) static void devlink_trap_unregister(struct devlink *devlink,
				    const struct devlink_trap *trap)
{
	struct devlink_trap_item *trap_item;

	trap_item = devlink_trap_item_lookup(devlink, trap->name);
	if (WARN_ON_ONCE(!trap_item))
		return;

	devlink_trap_notify(devlink, trap_item, DEVLINK_CMD_TRAP_DEL);
	list_del(&trap_item->list);
	if (devlink->ops->trap_fini)
		devlink->ops->trap_fini(devlink, trap, trap_item);
	devlink_trap_item_group_unlink(devlink, trap_item);
	free_percpu(trap_item->stats);
	kfree(trap_item);
}