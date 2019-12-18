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
struct TYPE_2__ {int len; } ;
struct property {TYPE_1__ val; } ;
struct node {struct node* parent; } ;
struct dt_info {int dtsflags; struct node* dt; } ;
struct check {int dummy; } ;
typedef  int /*<<< orphan*/  cell_t ;

/* Variables and functions */
 int DTSF_PLUGIN ; 
 int /*<<< orphan*/  FAIL (struct check*,struct dt_info*,struct node*,char*) ; 
 int /*<<< orphan*/  FAIL_PROP (struct check*,struct dt_info*,struct node*,struct property*,char*,...) ; 
 struct node* get_node_by_phandle (struct node*,int) ; 
 struct property* get_property (struct node*,char*) ; 
 scalar_t__ node_is_interrupt_provider (struct node*) ; 
 int propval_cell (struct property*) ; 

__attribute__((used)) static void check_interrupts_property(struct check *c,
				      struct dt_info *dti,
				      struct node *node)
{
	struct node *root = dti->dt;
	struct node *irq_node = NULL, *parent = node;
	struct property *irq_prop, *prop = NULL;
	int irq_cells, phandle;

	irq_prop = get_property(node, "interrupts");
	if (!irq_prop)
		return;

	if (irq_prop->val.len % sizeof(cell_t))
		FAIL_PROP(c, dti, node, irq_prop, "size (%d) is invalid, expected multiple of %zu",
		     irq_prop->val.len, sizeof(cell_t));

	while (parent && !prop) {
		if (parent != node && node_is_interrupt_provider(parent)) {
			irq_node = parent;
			break;
		}

		prop = get_property(parent, "interrupt-parent");
		if (prop) {
			phandle = propval_cell(prop);
			if ((phandle == 0) || (phandle == -1)) {
				/* Give up if this is an overlay with
				 * external references */
				if (dti->dtsflags & DTSF_PLUGIN)
					return;
				FAIL_PROP(c, dti, parent, prop, "Invalid phandle");
				continue;
			}

			irq_node = get_node_by_phandle(root, phandle);
			if (!irq_node) {
				FAIL_PROP(c, dti, parent, prop, "Bad phandle");
				return;
			}
			if (!node_is_interrupt_provider(irq_node))
				FAIL(c, dti, irq_node,
				     "Missing interrupt-controller or interrupt-map property");

			break;
		}

		parent = parent->parent;
	}

	if (!irq_node) {
		FAIL(c, dti, node, "Missing interrupt-parent");
		return;
	}

	prop = get_property(irq_node, "#interrupt-cells");
	if (!prop) {
		FAIL(c, dti, irq_node, "Missing #interrupt-cells in interrupt-parent");
		return;
	}

	irq_cells = propval_cell(prop);
	if (irq_prop->val.len % (irq_cells * sizeof(cell_t))) {
		FAIL_PROP(c, dti, node, prop,
			  "size is (%d), expected multiple of %d",
			  irq_prop->val.len, (int)(irq_cells * sizeof(cell_t)));
	}
}