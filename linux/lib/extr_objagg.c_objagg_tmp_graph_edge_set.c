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
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int objagg_tmp_graph_edge_index (struct objagg_tmp_graph*,int,int) ; 

__attribute__((used)) static void objagg_tmp_graph_edge_set(struct objagg_tmp_graph *graph,
				      int parent_index, int index)
{
	int edge_index = objagg_tmp_graph_edge_index(graph, index,
						     parent_index);

	__set_bit(edge_index, graph->edges);
}