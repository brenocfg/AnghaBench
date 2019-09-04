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
struct slot {int /*<<< orphan*/  work; int /*<<< orphan*/  lock; struct controller* ctrl; int /*<<< orphan*/  state; } ;
struct pci_bus {int /*<<< orphan*/  devices; } ;
struct controller {struct slot* slot; } ;
struct TYPE_2__ {struct pci_bus* subordinate; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OFF_STATE ; 
 int /*<<< orphan*/  ON_STATE ; 
 TYPE_1__* ctrl_dev (struct controller*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct slot* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_sem ; 
 int /*<<< orphan*/  pciehp_queue_pushbutton_work ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcie_init_slot(struct controller *ctrl)
{
	struct pci_bus *subordinate = ctrl_dev(ctrl)->subordinate;
	struct slot *slot;

	slot = kzalloc(sizeof(*slot), GFP_KERNEL);
	if (!slot)
		return -ENOMEM;

	down_read(&pci_bus_sem);
	slot->state = list_empty(&subordinate->devices) ? OFF_STATE : ON_STATE;
	up_read(&pci_bus_sem);

	slot->ctrl = ctrl;
	mutex_init(&slot->lock);
	INIT_DELAYED_WORK(&slot->work, pciehp_queue_pushbutton_work);
	ctrl->slot = slot;
	return 0;
}