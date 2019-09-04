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
struct pci_func {size_t device; struct pci_func* next; } ;

/* Variables and functions */
 struct pci_func** cpqhp_slot_list ; 

struct pci_func *cpqhp_slot_find(u8 bus, u8 device, u8 index)
{
	int found = -1;
	struct pci_func *func;

	func = cpqhp_slot_list[bus];

	if ((func == NULL) || ((func->device == device) && (index == 0)))
		return func;

	if (func->device == device)
		found++;

	while (func->next != NULL) {
		func = func->next;

		if (func->device == device)
			found++;

		if (found == index)
			return func;
	}

	return NULL;
}