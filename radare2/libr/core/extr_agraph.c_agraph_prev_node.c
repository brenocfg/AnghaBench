#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  curnode; } ;
struct TYPE_10__ {int /*<<< orphan*/  gnode; scalar_t__ is_dummy; } ;
typedef  TYPE_1__ RANode ;
typedef  TYPE_2__ RAGraph ;

/* Variables and functions */
 int /*<<< orphan*/  agraph_update_seek (TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  find_near_of (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* get_anode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_agraph_set_curnode (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static void agraph_prev_node(RAGraph *g) {
	RANode *a = get_anode (find_near_of (g, g->curnode, false));
	while (a && a->is_dummy) {
		a = get_anode (find_near_of (g, a->gnode, false));
	}
	r_agraph_set_curnode (g, a);
	agraph_update_seek (g, get_anode (g->curnode), false);
}