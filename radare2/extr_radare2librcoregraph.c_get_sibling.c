#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* layers; } ;
struct TYPE_8__ {int pos_in_layer; size_t layer; } ;
struct TYPE_7__ {int /*<<< orphan*/ ** nodes; } ;
typedef  int /*<<< orphan*/  RGraphNode ;
typedef  TYPE_2__ RANode ;
typedef  TYPE_3__ RAGraph ;

/* Variables and functions */
 scalar_t__ is_valid_pos (TYPE_3__ const*,size_t,int) ; 

__attribute__((used)) static RGraphNode *get_sibling(const RAGraph *g, const RANode *n, int is_left, int is_adjust_class) {
	RGraphNode *res = NULL;
	int pos = n->pos_in_layer;

	if ((is_left && is_adjust_class) || (!is_left && !is_adjust_class)) {
		pos++;
	} else {
		pos--;
	}

	if (is_valid_pos (g, n->layer, pos)) {
		res = g->layers[n->layer].nodes[pos];
	}
	return res;
}