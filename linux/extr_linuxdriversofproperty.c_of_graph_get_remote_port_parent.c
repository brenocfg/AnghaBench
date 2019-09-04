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
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_graph_get_port_parent (struct device_node*) ; 
 struct device_node* of_graph_get_remote_endpoint (struct device_node const*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

struct device_node *of_graph_get_remote_port_parent(
			       const struct device_node *node)
{
	struct device_node *np, *pp;

	/* Get remote endpoint node. */
	np = of_graph_get_remote_endpoint(node);

	pp = of_graph_get_port_parent(np);

	of_node_put(np);

	return pp;
}