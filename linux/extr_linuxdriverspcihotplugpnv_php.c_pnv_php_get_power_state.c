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
typedef  void* uint8_t ;
typedef  void* u8 ;
struct pnv_php_slot {int /*<<< orphan*/  pdev; int /*<<< orphan*/  id; } ;
struct hotplug_slot {TYPE_1__* info; struct pnv_php_slot* private; } ;
struct TYPE_2__ {void* power_status; } ;

/* Variables and functions */
 void* OPAL_PCI_SLOT_POWER_ON ; 
 int /*<<< orphan*/  pci_warn (int /*<<< orphan*/ ,char*,int) ; 
 int pnv_pci_get_power_state (int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static int pnv_php_get_power_state(struct hotplug_slot *slot, u8 *state)
{
	struct pnv_php_slot *php_slot = slot->private;
	uint8_t power_state = OPAL_PCI_SLOT_POWER_ON;
	int ret;

	/*
	 * Retrieve power status from firmware. If we fail
	 * getting that, the power status fails back to
	 * be on.
	 */
	ret = pnv_pci_get_power_state(php_slot->id, &power_state);
	if (ret) {
		pci_warn(php_slot->pdev, "Error %d getting power status\n",
			 ret);
	} else {
		*state = power_state;
		slot->info->power_status = power_state;
	}

	return 0;
}