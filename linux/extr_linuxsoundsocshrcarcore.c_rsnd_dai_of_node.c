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
struct rsnd_priv {int dummy; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSND_NODE_DAI ; 
 struct device_node* of_get_child_by_name (struct device_node*,int /*<<< orphan*/ ) ; 
 struct device_node* of_graph_get_next_endpoint (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device* rsnd_priv_to_dev (struct rsnd_priv*) ; 

__attribute__((used)) static struct device_node *rsnd_dai_of_node(struct rsnd_priv *priv,
					    int *is_graph)
{
	struct device *dev = rsnd_priv_to_dev(priv);
	struct device_node *np = dev->of_node;
	struct device_node *dai_node;
	struct device_node *ret;

	*is_graph = 0;

	/*
	 * parse both previous dai (= rcar_sound,dai), and
	 * graph dai (= ports/port)
	 */
	dai_node = of_get_child_by_name(np, RSND_NODE_DAI);
	if (dai_node) {
		ret = dai_node;
		goto of_node_compatible;
	}

	ret = np;

	dai_node = of_graph_get_next_endpoint(np, NULL);
	if (dai_node)
		goto of_node_graph;

	return NULL;

of_node_graph:
	*is_graph = 1;
of_node_compatible:
	of_node_put(dai_node);

	return ret;
}