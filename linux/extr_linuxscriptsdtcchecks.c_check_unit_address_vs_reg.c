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
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct property {TYPE_1__ val; } ;
struct node {int dummy; } ;
struct dt_info {int dummy; } ;
struct check {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL (struct check*,struct dt_info*,struct node*,char*) ; 
 struct property* get_property (struct node*,char*) ; 
 scalar_t__ get_subnode (struct node*,char*) ; 
 char* get_unitname (struct node*) ; 

__attribute__((used)) static void check_unit_address_vs_reg(struct check *c, struct dt_info *dti,
				      struct node *node)
{
	const char *unitname = get_unitname(node);
	struct property *prop = get_property(node, "reg");

	if (get_subnode(node, "__overlay__")) {
		/* HACK: Overlay fragments are a special case */
		return;
	}

	if (!prop) {
		prop = get_property(node, "ranges");
		if (prop && !prop->val.len)
			prop = NULL;
	}

	if (prop) {
		if (!unitname[0])
			FAIL(c, dti, node, "node has a reg or ranges property, but no unit name");
	} else {
		if (unitname[0])
			FAIL(c, dti, node, "node has a unit name, but no reg property");
	}
}