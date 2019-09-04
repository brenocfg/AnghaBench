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
struct acpiphp_slot {int flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int SLOT_ENABLED ; 
 int SLOT_IS_GOING_AWAY ; 
 int /*<<< orphan*/  enable_slot (struct acpiphp_slot*,int) ; 
 int /*<<< orphan*/  pci_lock_rescan_remove () ; 
 int /*<<< orphan*/  pci_unlock_rescan_remove () ; 

int acpiphp_enable_slot(struct acpiphp_slot *slot)
{
	pci_lock_rescan_remove();

	if (slot->flags & SLOT_IS_GOING_AWAY) {
		pci_unlock_rescan_remove();
		return -ENODEV;
	}

	/* configure all functions */
	if (!(slot->flags & SLOT_ENABLED))
		enable_slot(slot, false);

	pci_unlock_rescan_remove();
	return 0;
}