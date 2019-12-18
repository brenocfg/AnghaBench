#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_dm_hw_metadata {int /*<<< orphan*/  input_dev; int /*<<< orphan*/  trap_name; int /*<<< orphan*/  trap_group_name; } ;
struct devlink_trap_item {TYPE_2__* trap; struct devlink_trap_group_item* group_item; } ;
struct devlink_trap_group_item {TYPE_1__* group; } ;
struct devlink_port {scalar_t__ type; int /*<<< orphan*/  type_lock; int /*<<< orphan*/  type_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ DEVLINK_PORT_TYPE_ETH ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
devlink_trap_report_metadata_fill(struct net_dm_hw_metadata *hw_metadata,
				  const struct devlink_trap_item *trap_item,
				  struct devlink_port *in_devlink_port)
{
	struct devlink_trap_group_item *group_item = trap_item->group_item;

	hw_metadata->trap_group_name = group_item->group->name;
	hw_metadata->trap_name = trap_item->trap->name;

	spin_lock(&in_devlink_port->type_lock);
	if (in_devlink_port->type == DEVLINK_PORT_TYPE_ETH)
		hw_metadata->input_dev = in_devlink_port->type_dev;
	spin_unlock(&in_devlink_port->type_lock);
}