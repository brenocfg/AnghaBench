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
struct property {int dummy; } ;
struct node {int dummy; } ;
struct dt_info {int /*<<< orphan*/  dt; } ;
struct check {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_PROP (struct check*,struct dt_info*,struct node*,struct property*,char*) ; 
 struct node* get_node_by_phandle (int /*<<< orphan*/ ,int) ; 
 struct property* get_property (struct node*,char*) ; 
 int propval_cell (struct property*) ; 

__attribute__((used)) static struct node *get_remote_endpoint(struct check *c, struct dt_info *dti,
					struct node *endpoint)
{
	int phandle;
	struct node *node;
	struct property *prop;

	prop = get_property(endpoint, "remote-endpoint");
	if (!prop)
		return NULL;

	phandle = propval_cell(prop);
	/* Give up if this is an overlay with external references */
	if (phandle == 0 || phandle == -1)
		return NULL;

	node = get_node_by_phandle(dti->dt, phandle);
	if (!node)
		FAIL_PROP(c, dti, endpoint, prop, "graph phandle is not valid");

	return node;
}