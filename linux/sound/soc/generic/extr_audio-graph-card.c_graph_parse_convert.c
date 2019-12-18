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
struct device {struct device_node* of_node; } ;
struct asoc_simple_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * PREFIX ; 
 int /*<<< orphan*/  asoc_simple_parse_convert (struct device*,struct device_node*,int /*<<< orphan*/ *,struct asoc_simple_data*) ; 
 struct device_node* of_get_parent (struct device_node*) ; 
 struct device_node* of_graph_get_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static void graph_parse_convert(struct device *dev,
				struct device_node *ep,
				struct asoc_simple_data *adata)
{
	struct device_node *top = dev->of_node;
	struct device_node *port = of_get_parent(ep);
	struct device_node *ports = of_get_parent(port);
	struct device_node *node = of_graph_get_port_parent(ep);

	asoc_simple_parse_convert(dev, top,   NULL,   adata);
	asoc_simple_parse_convert(dev, node,  PREFIX, adata);
	asoc_simple_parse_convert(dev, ports, NULL,   adata);
	asoc_simple_parse_convert(dev, port,  NULL,   adata);
	asoc_simple_parse_convert(dev, ep,    NULL,   adata);

	of_node_put(port);
	of_node_put(ports);
	of_node_put(node);
}