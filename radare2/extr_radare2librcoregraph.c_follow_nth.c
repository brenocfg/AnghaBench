#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  graph; int /*<<< orphan*/  curnode; } ;
struct TYPE_7__ {int /*<<< orphan*/  gnode; scalar_t__ is_dummy; } ;
typedef  int /*<<< orphan*/  RGraphNode ;
typedef  TYPE_1__ RANode ;
typedef  TYPE_2__ RAGraph ;

/* Variables and functions */
 TYPE_1__* get_anode (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  r_agraph_set_curnode (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/ * r_graph_nth_neighbour (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void follow_nth(RAGraph *g, int nth) {
	const RGraphNode *cn = r_graph_nth_neighbour (g->graph, g->curnode, nth);
	RANode *a = get_anode (cn);

	while (a && a->is_dummy) {
		cn = r_graph_nth_neighbour (g->graph, a->gnode, 0);
		a = get_anode (cn);
	}
	if (a) {
		r_agraph_set_curnode (g, a);
	}
}