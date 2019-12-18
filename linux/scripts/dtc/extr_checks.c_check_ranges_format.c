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
struct node {int /*<<< orphan*/  fullpath; struct node* parent; } ;
struct dt_info {int dummy; } ;
struct check {int dummy; } ;
typedef  int /*<<< orphan*/  cell_t ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_PROP (struct check*,struct dt_info*,struct node*,struct property*,char*,...) ; 
 struct property* get_property (struct node*,char*) ; 
 int node_addr_cells (struct node*) ; 
 int node_size_cells (struct node*) ; 

__attribute__((used)) static void check_ranges_format(struct check *c, struct dt_info *dti,
				struct node *node)
{
	struct property *prop;
	int c_addr_cells, p_addr_cells, c_size_cells, p_size_cells, entrylen;

	prop = get_property(node, "ranges");
	if (!prop)
		return;

	if (!node->parent) {
		FAIL_PROP(c, dti, node, prop, "Root node has a \"ranges\" property");
		return;
	}

	p_addr_cells = node_addr_cells(node->parent);
	p_size_cells = node_size_cells(node->parent);
	c_addr_cells = node_addr_cells(node);
	c_size_cells = node_size_cells(node);
	entrylen = (p_addr_cells + c_addr_cells + c_size_cells) * sizeof(cell_t);

	if (prop->val.len == 0) {
		if (p_addr_cells != c_addr_cells)
			FAIL_PROP(c, dti, node, prop, "empty \"ranges\" property but its "
				  "#address-cells (%d) differs from %s (%d)",
				  c_addr_cells, node->parent->fullpath,
				  p_addr_cells);
		if (p_size_cells != c_size_cells)
			FAIL_PROP(c, dti, node, prop, "empty \"ranges\" property but its "
				  "#size-cells (%d) differs from %s (%d)",
				  c_size_cells, node->parent->fullpath,
				  p_size_cells);
	} else if ((prop->val.len % entrylen) != 0) {
		FAIL_PROP(c, dti, node, prop, "\"ranges\" property has invalid length (%d bytes) "
			  "(parent #address-cells == %d, child #address-cells == %d, "
			  "#size-cells == %d)", prop->val.len,
			  p_addr_cells, c_addr_cells, c_size_cells);
	}
}