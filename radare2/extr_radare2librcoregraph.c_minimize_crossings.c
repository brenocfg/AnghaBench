#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int n_layers; int /*<<< orphan*/  layers; int /*<<< orphan*/  graph; } ;
typedef  TYPE_1__ RAGraph ;

/* Variables and functions */
 int layer_sweep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void minimize_crossings(const RAGraph *g) {
	int i, cross_changed, max_changes = 4096;

	do {
		cross_changed = false;
		max_changes--;

		for (i = 0; i < g->n_layers; ++i) {
			int rc = layer_sweep (g->graph, g->layers, g->n_layers, i, true);
			if (rc == -1) {
				return;
			}
			cross_changed |= !!rc;
		}
	} while (cross_changed && max_changes);

	max_changes = 4096;

	do {
		cross_changed = false;
		max_changes--;

		for (i = g->n_layers - 1; i >= 0; --i) {
			int rc = layer_sweep (g->graph, g->layers, g->n_layers, i, false);
			if (rc == -1) {
				return;
			}
			cross_changed |= !!rc;
		}
	} while (cross_changed && max_changes);
}