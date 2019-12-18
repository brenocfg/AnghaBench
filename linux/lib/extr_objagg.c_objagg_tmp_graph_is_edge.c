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
struct objagg_tmp_graph {int /*<<< orphan*/  edges; } ;

/* Variables and functions */
 int objagg_tmp_graph_edge_index (struct objagg_tmp_graph*,int,int) ; 
 int test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool objagg_tmp_graph_is_edge(struct objagg_tmp_graph *graph,
				     int parent_index, int index)
{
	int edge_index = objagg_tmp_graph_edge_index(graph, index,
						     parent_index);

	return test_bit(edge_index, graph->edges);
}