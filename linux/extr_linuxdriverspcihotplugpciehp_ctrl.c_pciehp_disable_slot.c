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
struct slot {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; struct controller* ctrl; } ;
struct controller {TYPE_1__* pcie; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {TYPE_2__* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  OFF_STATE ; 
 int __pciehp_disable_slot (struct slot*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pciehp_disable_slot(struct slot *slot)
{
	struct controller *ctrl = slot->ctrl;
	int ret;

	pm_runtime_get_sync(&ctrl->pcie->port->dev);
	ret = __pciehp_disable_slot(slot);
	pm_runtime_put(&ctrl->pcie->port->dev);

	mutex_lock(&slot->lock);
	slot->state = OFF_STATE;
	mutex_unlock(&slot->lock);

	return ret;
}