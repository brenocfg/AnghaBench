#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int min; int max; } ;
struct TYPE_10__ {int rb_max_addr; scalar_t__ _size; TYPE_1__ meta; } ;
struct TYPE_9__ {struct TYPE_9__** child; } ;
typedef  TYPE_2__ RBNode ;
typedef  TYPE_3__ RAnalFunction ;

/* Variables and functions */
 TYPE_3__* FCN_CONTAINER (TYPE_2__*) ; 
 int /*<<< orphan*/  set_meta_if_needed (TYPE_3__*) ; 

__attribute__((used)) static void _fcn_tree_calc_max_addr(RBNode *node) {
	int i;
	RAnalFunction *fcn = FCN_CONTAINER (node);
	set_meta_if_needed (fcn);
	fcn->rb_max_addr = fcn->meta.min + (fcn->_size == 0 ? 0 : (fcn->meta.max - fcn->meta.min - 1));
	for (i = 0; i < 2; i++) {
		if (node->child[i]) {
			RAnalFunction *fcn1 = FCN_CONTAINER (node->child[i]);
			if (fcn1->rb_max_addr > fcn->rb_max_addr) {
				fcn->rb_max_addr = fcn1->rb_max_addr;
			}
		}
	}
}