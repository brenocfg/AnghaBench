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
struct objagg_tmp_graph {struct objagg_tmp_graph* nodes; struct objagg_tmp_graph* edges; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct objagg_tmp_graph*) ; 

__attribute__((used)) static void objagg_tmp_graph_destroy(struct objagg_tmp_graph *graph)
{
	kfree(graph->edges);
	kfree(graph->nodes);
	kfree(graph);
}