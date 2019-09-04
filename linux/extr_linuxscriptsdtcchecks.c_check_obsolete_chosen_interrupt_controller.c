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
struct dt_info {struct node* dt; } ;
struct check {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL_PROP (struct check*,struct dt_info*,struct node*,struct property*,char*) ; 
 struct node* get_node_by_path (struct node*,char*) ; 
 struct property* get_property (struct node*,char*) ; 

__attribute__((used)) static void check_obsolete_chosen_interrupt_controller(struct check *c,
						       struct dt_info *dti,
						       struct node *node)
{
	struct node *dt = dti->dt;
	struct node *chosen;
	struct property *prop;

	if (node != dt)
		return;


	chosen = get_node_by_path(dt, "/chosen");
	if (!chosen)
		return;

	prop = get_property(chosen, "interrupt-controller");
	if (prop)
		FAIL_PROP(c, dti, node, prop,
			  "/chosen has obsolete \"interrupt-controller\" property");
}