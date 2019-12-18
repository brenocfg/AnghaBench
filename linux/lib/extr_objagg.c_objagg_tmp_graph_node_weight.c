#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct objagg_tmp_node {TYPE_2__* objagg_obj; scalar_t__ crossed_out; } ;
struct objagg_tmp_graph {int nodes_count; struct objagg_tmp_node* nodes; } ;
struct TYPE_3__ {unsigned int user_count; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  objagg_tmp_graph_is_edge (struct objagg_tmp_graph*,unsigned int,int) ; 

__attribute__((used)) static unsigned int objagg_tmp_graph_node_weight(struct objagg_tmp_graph *graph,
						 unsigned int index)
{
	struct objagg_tmp_node *node = &graph->nodes[index];
	unsigned int weight = node->objagg_obj->stats.user_count;
	int j;

	/* Node weight is sum of node users and all other nodes users
	 * that this node can represent with delta.
	 */

	for (j = 0; j < graph->nodes_count; j++) {
		if (!objagg_tmp_graph_is_edge(graph, index, j))
			continue;
		node = &graph->nodes[j];
		if (node->crossed_out)
			continue;
		weight += node->objagg_obj->stats.user_count;
	}
	return weight;
}