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
struct TYPE_3__ {int is_callgraph; int need_reload_nodes; int force_update_seek; } ;
typedef  TYPE_1__ RAGraph ;

/* Variables and functions */

__attribute__((used)) static void agraph_toggle_callgraph(RAGraph *g) {
	g->is_callgraph = !g->is_callgraph;
	g->need_reload_nodes = true;
	g->force_update_seek = true;
}