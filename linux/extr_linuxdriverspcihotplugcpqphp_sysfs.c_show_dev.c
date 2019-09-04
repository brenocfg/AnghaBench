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
struct slot {struct slot* next; int /*<<< orphan*/  device; int /*<<< orphan*/  bus; } ;
struct pci_resource {int base; int length; struct pci_resource* next; } ;
struct pci_func {struct pci_resource* bus_head; struct pci_resource* io_head; struct pci_resource* p_mem_head; struct pci_resource* mem_head; } ;
struct controller {struct slot* slot; } ;

/* Variables and functions */
 struct pci_func* cpqhp_slot_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static int show_dev(struct controller *ctrl, char *buf)
{
	char *out = buf;
	int index;
	struct pci_resource *res;
	struct pci_func *new_slot;
	struct slot *slot;

	slot = ctrl->slot;

	while (slot) {
		new_slot = cpqhp_slot_find(slot->bus, slot->device, 0);
		if (!new_slot)
			break;
		out += sprintf(out, "assigned resources: memory\n");
		index = 11;
		res = new_slot->mem_head;
		while (res && index--) {
			out += sprintf(out, "start = %8.8x, length = %8.8x\n", res->base, res->length);
			res = res->next;
		}
		out += sprintf(out, "assigned resources: prefetchable memory\n");
		index = 11;
		res = new_slot->p_mem_head;
		while (res && index--) {
			out += sprintf(out, "start = %8.8x, length = %8.8x\n", res->base, res->length);
			res = res->next;
		}
		out += sprintf(out, "assigned resources: IO\n");
		index = 11;
		res = new_slot->io_head;
		while (res && index--) {
			out += sprintf(out, "start = %8.8x, length = %8.8x\n", res->base, res->length);
			res = res->next;
		}
		out += sprintf(out, "assigned resources: bus numbers\n");
		index = 11;
		res = new_slot->bus_head;
		while (res && index--) {
			out += sprintf(out, "start = %8.8x, length = %8.8x\n", res->base, res->length);
			res = res->next;
		}
		slot = slot->next;
	}

	return out - buf;
}