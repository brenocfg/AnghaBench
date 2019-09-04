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
struct pci_slot {int /*<<< orphan*/  hotplug; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  might_sleep () ; 
 int pci_reset_hotplug_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_slot_reset (struct pci_slot*,int) ; 
 int /*<<< orphan*/  pci_slot_restore (struct pci_slot*) ; 
 int /*<<< orphan*/  pci_slot_save_and_disable (struct pci_slot*) ; 
 scalar_t__ pci_slot_trylock (struct pci_slot*) ; 
 int /*<<< orphan*/  pci_slot_unlock (struct pci_slot*) ; 

__attribute__((used)) static int __pci_reset_slot(struct pci_slot *slot)
{
	int rc;

	rc = pci_slot_reset(slot, 1);
	if (rc)
		return rc;

	pci_slot_save_and_disable(slot);

	if (pci_slot_trylock(slot)) {
		might_sleep();
		rc = pci_reset_hotplug_slot(slot->hotplug, 0);
		pci_slot_unlock(slot);
	} else
		rc = -EAGAIN;

	pci_slot_restore(slot);

	return rc;
}