#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int n_layers; int /*<<< orphan*/  graph; TYPE_1__* layers; } ;
struct TYPE_7__ {scalar_t__ is_dummy; } ;
struct TYPE_6__ {int n_nodes; int /*<<< orphan*/ ** nodes; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RGraphNode ;
typedef  TYPE_2__ RANode ;
typedef  TYPE_3__ RAGraph ;

/* Variables and functions */
 TYPE_2__* get_anode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hash_get_rlist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_graph_nth_neighbour (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_new () ; 
 int /*<<< orphan*/ * sdb_new0 () ; 

__attribute__((used)) static Sdb *compute_vertical_nodes(const RAGraph *g) {
	Sdb *res = sdb_new0 ();
	int i, j;

	for (i = 0; i < g->n_layers; ++i) {
		for (j = 0; j < g->layers[i].n_nodes; ++j) {
			RGraphNode *gn = g->layers[i].nodes[j];
			const RList *Ln = hash_get_rlist (res, gn);
			const RANode *an = get_anode (gn);

			if (!Ln) {
				RList *vert = r_list_new ();
				hash_set (res, gn, vert);
				if (an->is_dummy) {
					RGraphNode *next = gn;
					const RANode *anext = get_anode (next);

					while (anext->is_dummy) {
						r_list_append (vert, next);
						next = r_graph_nth_neighbour (g->graph, next, 0);
						if (!next) {
							break;
						}
						anext = get_anode (next);
					}
				} else {
					r_list_append (vert, gn);
				}
			}
		}
	}

	return res;
}