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
struct devlink_trap_item {int /*<<< orphan*/  action; } ;
struct devlink_trap {int /*<<< orphan*/  name; } ;
struct devlink {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* trap_action_set ) (struct devlink*,struct devlink_trap const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_TRAP_ACTION_DROP ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 struct devlink_trap_item* devlink_trap_item_lookup (struct devlink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct devlink*,struct devlink_trap const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void devlink_trap_disable(struct devlink *devlink,
				 const struct devlink_trap *trap)
{
	struct devlink_trap_item *trap_item;

	trap_item = devlink_trap_item_lookup(devlink, trap->name);
	if (WARN_ON_ONCE(!trap_item))
		return;

	devlink->ops->trap_action_set(devlink, trap, DEVLINK_TRAP_ACTION_DROP);
	trap_item->action = DEVLINK_TRAP_ACTION_DROP;
}