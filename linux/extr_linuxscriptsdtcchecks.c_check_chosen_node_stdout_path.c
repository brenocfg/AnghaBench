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
struct property {int /*<<< orphan*/  name; } ;
struct node {int /*<<< orphan*/  name; } ;
struct dt_info {int dummy; } ;
struct check {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_PROP (struct check*,struct dt_info*,struct node*,struct property*,char*) ; 
 int /*<<< orphan*/  check_is_string (struct check*,struct dt_info*,struct node*) ; 
 struct property* get_property (struct node*,char*) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void check_chosen_node_stdout_path(struct check *c, struct dt_info *dti,
					  struct node *node)
{
	struct property *prop;

	if (!streq(node->name, "chosen"))
		return;

	prop = get_property(node, "stdout-path");
	if (!prop) {
		prop = get_property(node, "linux,stdout-path");
		if (!prop)
			return;
		FAIL_PROP(c, dti, node, prop, "Use 'stdout-path' instead");
	}

	c->data = prop->name;
	check_is_string(c, dti, node);
}