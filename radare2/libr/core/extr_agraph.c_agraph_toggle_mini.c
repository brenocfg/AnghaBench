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
struct TYPE_9__ {int /*<<< orphan*/  event_data; } ;
struct TYPE_8__ {int need_update_dim; int /*<<< orphan*/  curnode; } ;
struct TYPE_7__ {int is_mini; } ;
typedef  TYPE_1__ RANode ;
typedef  TYPE_2__ RAGraph ;

/* Variables and functions */
 int /*<<< orphan*/  agraph_refresh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agraph_set_layout (TYPE_2__*) ; 
 TYPE_1__* get_anode (int /*<<< orphan*/ ) ; 
 TYPE_3__* r_cons_singleton () ; 

__attribute__((used)) static void agraph_toggle_mini(RAGraph *g) {
	RANode *n = get_anode (g->curnode);
	if (n) {
		n->is_mini = !n->is_mini;
	}
	g->need_update_dim = 1;
	agraph_refresh (r_cons_singleton ()->event_data);
	agraph_set_layout ((RAGraph *) g);
}