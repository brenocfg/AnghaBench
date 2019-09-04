#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int n_layers; TYPE_1__* layers; } ;
struct TYPE_12__ {int pos_in_layer; size_t layer; scalar_t__ is_dummy; } ;
struct TYPE_11__ {int n_nodes; int /*<<< orphan*/ ** nodes; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  int /*<<< orphan*/  RGraphNode ;
typedef  TYPE_2__ RANode ;
typedef  TYPE_3__ RAGraph ;

/* Variables and functions */
 int /*<<< orphan*/  adjust_directions (TYPE_3__ const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* get_anode (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * get_right_dummy (TYPE_3__ const*,int /*<<< orphan*/  const*) ; 
 int hash_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ is_valid_pos (TYPE_3__ const*,int,int) ; 
 int /*<<< orphan*/  place_sequence (TYPE_3__ const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  set_dist_nodes (TYPE_3__ const*,int,int,int) ; 

__attribute__((used)) static void original_traverse_l(const RAGraph *g, Sdb *D, Sdb *P, int from_up) {
	int i, k, va, vr;

	for (i = from_up? 0: g->n_layers - 1;
			(from_up && i < g->n_layers) || (!from_up && i >= 0);
			i = from_up? i + 1: i - 1) {
		int j;
		const RGraphNode *bm = NULL;
		const RANode *bma = NULL;

		j = 0;
		while (j < g->layers[i].n_nodes && !bm) {
			const RGraphNode *gn = g->layers[i].nodes[j];
			const RANode *an = get_anode (gn);
			if (an && an->is_dummy) {
				va = 0;
				vr = j;
				bm = gn;
				bma = an;
			}
			j++;
		}
		if (!bm) {
			va = 0;
			vr = g->layers[i].n_nodes;
		}
		place_sequence (g, i, NULL, bm, from_up, va, vr);
		for (k = va; k < vr - 1; k++) {
			set_dist_nodes (g, i, k, k + 1);
		}
		if (is_valid_pos (g, i, vr - 1) && bm) {
			set_dist_nodes (g, i, vr - 1, bma->pos_in_layer);
		}
		while (bm) {
			const RGraphNode *bp = get_right_dummy (g, bm);
			const RANode *bpa = NULL;
			bma = get_anode (bm);

			if (!bp) {
				va = bma->pos_in_layer + 1;
				vr = g->layers[bma->layer].n_nodes;
				place_sequence (g, i, bm, NULL, from_up, va, vr);
				for (k = va; k < vr - 1; ++k) {
					set_dist_nodes (g, i, k, k + 1);
				}

				if (is_valid_pos (g, i, va)) {
					set_dist_nodes (g, i, bma->pos_in_layer, va);
				}
			} else if (hash_get_int (D, bm) == from_up) {
				bpa = get_anode (bp);
				va = bma->pos_in_layer + 1;
				vr = bpa->pos_in_layer;
				place_sequence (g, i, bm, bp, from_up, va, vr);
				hash_set (P, bm, true);
			}
			bm = bp;
		}
		adjust_directions (g, i, from_up, D, P);
	}
}