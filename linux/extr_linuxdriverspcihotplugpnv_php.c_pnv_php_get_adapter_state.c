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
struct TYPE_2__ {void* adapter_status; } ;

/* Variables and functions */
 void* OPAL_PCI_SLOT_EMPTY ; 
 int /*<<< orphan*/  pci_warn (int /*<<< orphan*/ ,char*,int) ; 
 int pnv_pci_get_presence_state (int /*<<< orphan*/ ,void**) ; 

__attribute__((used)) static int pnv_php_get_adapter_state(struct hotplug_slot *slot, u8 *state)
{
	struct pnv_php_slot *php_slot = slot->private;
	uint8_t presence = OPAL_PCI_SLOT_EMPTY;
	int ret;

	/*
	 * Retrieve presence status from firmware. If we can't
	 * get that, it will fail back to be empty.
	 */
	ret = pnv_pci_get_presence_state(php_slot->id, &presence);
	if (ret >= 0) {
		*state = presence;
		slot->info->adapter_status = presence;
		ret = 0;
	} else {
		pci_warn(php_slot->pdev, "Error %d getting presence\n", ret);
	}

	return ret;
}