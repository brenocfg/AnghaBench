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
typedef  size_t u8 ;
struct pci_func {int* config_space; size_t bus; struct pci_func* next; } ;

/* Variables and functions */
 struct pci_func** cpqhp_slot_list ; 
 int /*<<< orphan*/  kfree (struct pci_func*) ; 
 int /*<<< orphan*/  slot_remove (struct pci_func*) ; 

__attribute__((used)) static int bridge_slot_remove(struct pci_func *bridge)
{
	u8 subordinateBus, secondaryBus;
	u8 tempBus;
	struct pci_func *next;

	secondaryBus = (bridge->config_space[0x06] >> 8) & 0xFF;
	subordinateBus = (bridge->config_space[0x06] >> 16) & 0xFF;

	for (tempBus = secondaryBus; tempBus <= subordinateBus; tempBus++) {
		next = cpqhp_slot_list[tempBus];

		while (!slot_remove(next))
			next = cpqhp_slot_list[tempBus];
	}

	next = cpqhp_slot_list[bridge->bus];

	if (next == NULL)
		return 1;

	if (next == bridge) {
		cpqhp_slot_list[bridge->bus] = bridge->next;
		goto out;
	}

	while ((next->next != bridge) && (next->next != NULL))
		next = next->next;

	if (next->next != bridge)
		return 2;
	next->next = bridge->next;
out:
	kfree(bridge);
	return 0;
}