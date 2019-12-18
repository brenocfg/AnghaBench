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
struct TYPE_8__ {int n_layers; TYPE_1__* layers; int /*<<< orphan*/  graph; } ;
struct TYPE_7__ {int pos_in_layer; size_t layer; scalar_t__ is_dummy; } ;
struct TYPE_6__ {int n_nodes; int /*<<< orphan*/ ** nodes; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RGraphNode ;
typedef  TYPE_2__ RANode ;
typedef  TYPE_3__ RAGraph ;

/* Variables and functions */
 TYPE_2__* get_anode (int /*<<< orphan*/  const*) ; 
 int hash_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_graph_innodes (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * r_graph_nth_neighbour (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * r_list_get_n (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adjust_directions(const RAGraph *g, int i, int from_up, Sdb *D, Sdb *P) {
	const RGraphNode *vm = NULL, *wm = NULL;
	const RANode *vma = NULL, *wma = NULL;
	int j, d = from_up? 1: -1;

	if (i + d < 0 || i + d >= g->n_layers) {
		return;
	}
	for (j = 0; j < g->layers[i + d].n_nodes; ++j) {
		const RGraphNode *wp, *vp = g->layers[i + d].nodes[j];
		const RANode *wpa, *vpa = get_anode (vp);

		if (!vpa || !vpa->is_dummy) {
			continue;
		}
		if (from_up) {
			wp = r_list_get_n (r_graph_innodes (g->graph, vp), 0);
		} else {
			wp = r_graph_nth_neighbour (g->graph, vp, 0);
		}
		wpa = get_anode (wp);
		if (!wpa || !wpa->is_dummy) {
			continue;
		}
		if (vm) {
			int p = hash_get_int (P, wm);
			int k;

			for (k = wma->pos_in_layer + 1; k < wpa->pos_in_layer; ++k) {
				const RGraphNode *w = g->layers[wma->layer].nodes[k];
				const RANode *aw = get_anode (w);
				if (aw && aw->is_dummy) {
					p &= hash_get_int (P, w);
				}
			}
			if (p) {
				hash_set (D, vm, from_up);
				for (k = vma->pos_in_layer + 1; k < vpa->pos_in_layer; ++k) {
					const RGraphNode *v = g->layers[vma->layer].nodes[k];
					const RANode *av = get_anode (v);
					if (av && av->is_dummy) {
						hash_set (D, v, from_up);
					}
				}
			}
		}
		vm = vp;
		wm = wp;
		vma = get_anode (vm);
		wma = get_anode (wm);
	}
}