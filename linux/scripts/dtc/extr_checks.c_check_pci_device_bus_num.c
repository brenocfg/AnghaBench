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
struct TYPE_2__ {scalar_t__ val; } ;
struct property {TYPE_1__ val; } ;
struct node {struct node* parent; int /*<<< orphan*/ * bus; } ;
struct dt_info {int dummy; } ;
struct check {int dummy; } ;
typedef  int /*<<< orphan*/  cell_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_PROP (struct check*,struct dt_info*,struct node*,struct property*,char*,unsigned int,unsigned int,unsigned int) ; 
 int fdt32_to_cpu (int /*<<< orphan*/ ) ; 
 struct property* get_property (struct node*,char*) ; 
 int /*<<< orphan*/  pci_bus ; 

__attribute__((used)) static void check_pci_device_bus_num(struct check *c, struct dt_info *dti, struct node *node)
{
	struct property *prop;
	unsigned int bus_num, min_bus, max_bus;
	cell_t *cells;

	if (!node->parent || (node->parent->bus != &pci_bus))
		return;

	prop = get_property(node, "reg");
	if (!prop)
		return;

	cells = (cell_t *)prop->val.val;
	bus_num = (fdt32_to_cpu(cells[0]) & 0x00ff0000) >> 16;

	prop = get_property(node->parent, "bus-range");
	if (!prop) {
		min_bus = max_bus = 0;
	} else {
		cells = (cell_t *)prop->val.val;
		min_bus = fdt32_to_cpu(cells[0]);
		max_bus = fdt32_to_cpu(cells[0]);
	}
	if ((bus_num < min_bus) || (bus_num > max_bus))
		FAIL_PROP(c, dti, node, prop, "PCI bus number %d out of range, expected (%d - %d)",
			  bus_num, min_bus, max_bus);
}