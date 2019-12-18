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
struct node {int /*<<< orphan*/  basenamelen; int /*<<< orphan*/  name; int /*<<< orphan*/ * bus; } ;
struct dt_info {int dummy; } ;
struct check {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL (struct check*,struct dt_info*,struct node*,char*) ; 
 int /*<<< orphan*/  check_graph_reg (struct check*,struct dt_info*,struct node*) ; 
 int /*<<< orphan*/  graph_port_bus ; 
 int /*<<< orphan*/  strprefixeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void check_graph_port(struct check *c, struct dt_info *dti,
			     struct node *node)
{
	if (node->bus != &graph_port_bus)
		return;

	if (!strprefixeq(node->name, node->basenamelen, "port"))
		FAIL(c, dti, node, "graph port node name should be 'port'");

	check_graph_reg(c, dti, node);
}