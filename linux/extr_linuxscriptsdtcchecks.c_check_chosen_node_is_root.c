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
struct node {scalar_t__ parent; int /*<<< orphan*/  name; } ;
struct dt_info {scalar_t__ dt; } ;
struct check {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL (struct check*,struct dt_info*,struct node*,char*) ; 
 int /*<<< orphan*/  streq (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void check_chosen_node_is_root(struct check *c, struct dt_info *dti,
				      struct node *node)
{
	if (!streq(node->name, "chosen"))
		return;

	if (node->parent != dti->dt)
		FAIL(c, dti, node, "chosen node must be at root node");
}