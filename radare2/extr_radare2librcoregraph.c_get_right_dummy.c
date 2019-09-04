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
struct TYPE_8__ {TYPE_1__* layers; } ;
struct TYPE_7__ {int layer; int pos_in_layer; scalar_t__ is_dummy; } ;
struct TYPE_6__ {int n_nodes; int /*<<< orphan*/  const** nodes; } ;
typedef  int /*<<< orphan*/  const RGraphNode ;
typedef  TYPE_2__ RANode ;
typedef  TYPE_3__ RAGraph ;

/* Variables and functions */
 TYPE_2__* get_anode (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static RGraphNode *get_right_dummy(const RAGraph *g, const RGraphNode *n) {
	const RANode *an = get_anode (n);
	if (!an) {
		return NULL;
	}
	int k, layer = an->layer;

	for (k = an->pos_in_layer + 1; k < g->layers[layer].n_nodes; ++k) {
		RGraphNode *gk = g->layers[layer].nodes[k];
		const RANode *ak = get_anode (gk);
		if (!ak) {
			break;
		}

		if (ak->is_dummy) {
			return gk;
		}
	}
	return NULL;
}