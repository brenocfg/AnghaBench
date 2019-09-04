#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  unit_addr ;
struct TYPE_3__ {int len; scalar_t__ val; } ;
struct property {TYPE_1__ val; } ;
struct node {TYPE_2__* parent; } ;
struct dt_info {int dummy; } ;
struct check {int dummy; } ;
typedef  int /*<<< orphan*/  cell_t ;
struct TYPE_4__ {int addr_cells; int size_cells; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL (struct check*,struct dt_info*,struct node*,char*,...) ; 
 int /*<<< orphan*/  FAIL_PROP (struct check*,struct dt_info*,struct node*,struct property*,char*,int) ; 
 struct property* get_property (struct node*,char*) ; 
 char* get_unitname (struct node*) ; 
 int propval_cell (struct property*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  streq (char const*,char*) ; 

__attribute__((used)) static void check_graph_reg(struct check *c, struct dt_info *dti,
			    struct node *node)
{
	char unit_addr[9];
	const char *unitname = get_unitname(node);
	struct property *prop;

	prop = get_property(node, "reg");
	if (!prop || !unitname)
		return;

	if (!(prop->val.val && prop->val.len == sizeof(cell_t))) {
		FAIL(c, dti, node, "graph node malformed 'reg' property");
		return;
	}

	snprintf(unit_addr, sizeof(unit_addr), "%x", propval_cell(prop));
	if (!streq(unitname, unit_addr))
		FAIL(c, dti, node, "graph node unit address error, expected \"%s\"",
		     unit_addr);

	if (node->parent->addr_cells != 1)
		FAIL_PROP(c, dti, node, get_property(node, "#address-cells"),
			  "graph node '#address-cells' is %d, must be 1",
			  node->parent->addr_cells);
	if (node->parent->size_cells != 0)
		FAIL_PROP(c, dti, node, get_property(node, "#size-cells"),
			  "graph node '#size-cells' is %d, must be 0",
			  node->parent->size_cells);
}