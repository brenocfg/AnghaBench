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
struct TYPE_3__ {int is_callgraph; int is_instep; int need_reload_nodes; int show_node_titles; int show_node_body; int force_update_seek; int edgemode; int hints; void* db; int /*<<< orphan*/  movspeed; int /*<<< orphan*/  zoom; void* nodes; int /*<<< orphan*/  graph; } ;
typedef  TYPE_1__ RAGraph ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_SPEED ; 
 int /*<<< orphan*/  ZOOM_DEFAULT ; 
 int /*<<< orphan*/  r_graph_new () ; 
 void* sdb_new0 () ; 

__attribute__((used)) static void agraph_init(RAGraph *g) {
	g->is_callgraph = false;
	g->is_instep = false;
	g->need_reload_nodes = true;
	g->show_node_titles = true;
	g->show_node_body = true;
	g->force_update_seek = true;
	g->graph = r_graph_new ();
	g->nodes = sdb_new0 ();
	g->edgemode = 2;
	g->zoom = ZOOM_DEFAULT;
	g->hints = 1;
	g->movspeed = DEFAULT_SPEED;
	g->db = sdb_new0 ();
}