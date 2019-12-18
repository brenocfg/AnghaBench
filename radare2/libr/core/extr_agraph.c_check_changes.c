#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_24__ {int sx; int sy; void* color; } ;
struct TYPE_23__ {int need_reload_nodes; int force_update_seek; int need_update_dim; int need_set_layout; TYPE_2__* update_seek_on; TYPE_4__* can; scalar_t__ curnode; void* hints; int /*<<< orphan*/  layout; int /*<<< orphan*/  is_callgraph; int /*<<< orphan*/  edgemode; int /*<<< orphan*/  zoom; int /*<<< orphan*/  graph; } ;
struct TYPE_22__ {int /*<<< orphan*/  title; } ;
struct TYPE_21__ {scalar_t__ config; int /*<<< orphan*/  offset; int /*<<< orphan*/  anal; } ;
typedef  TYPE_1__ RCore ;
typedef  int /*<<< orphan*/  RAnalFunction ;
typedef  TYPE_2__ RANode ;
typedef  TYPE_3__ RAGraph ;

/* Variables and functions */
 scalar_t__ UT64_MAX ; 
 int /*<<< orphan*/  agraph_reload_nodes (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  agraph_set_layout (TYPE_3__*) ; 
 int /*<<< orphan*/  agraph_update_title (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fold_asm_trace (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__* get_anode (scalar_t__) ; 
 char* get_title (scalar_t__) ; 
 int /*<<< orphan*/  is_mini (TYPE_3__*) ; 
 TYPE_2__* r_agraph_get_node (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  r_agraph_set_curnode (TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ r_anal_get_bbaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* r_config_get_i (scalar_t__,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  update_node_dimension (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_seek (TYPE_4__*,TYPE_2__*,int) ; 

__attribute__((used)) static int check_changes(RAGraph *g, int is_interactive, RCore *core, RAnalFunction *fcn) {
	int oldpos[2] = {
		0, 0
	};
	if (g->need_reload_nodes && core) {
		if (!g->update_seek_on && !g->force_update_seek) {
			// save scroll here
			oldpos[0] = g->can->sx;
			oldpos[1] = g->can->sy;
		}
		if (!agraph_reload_nodes (g, core, fcn)) {
			return false;
		}
	}
	if (fcn) {
		agraph_update_title (core, g, fcn);
	}
	if (core && core->config) {
		if (r_config_get_i (core->config, "graph.trace")) {
			// fold all bbs not traced
			fold_asm_trace (core, g);
		}
	}
	if (g->need_update_dim || g->need_reload_nodes || !is_interactive) {
		update_node_dimension (g->graph, is_mini (g), g->zoom, g->edgemode, g->is_callgraph, g->layout);
	}
	if (g->need_set_layout || g->need_reload_nodes || !is_interactive) {
		agraph_set_layout (g);
	}
	if (core) {
		ut64 off = r_anal_get_bbaddr (core->anal, core->offset);
		if (off == UT64_MAX) {
			return false;
		}
		char *title = get_title (off);
		RANode *cur_anode = get_anode (g->curnode);
		if (fcn && ((is_interactive && !cur_anode) || (cur_anode && strcmp (cur_anode->title, title)))) {
			g->update_seek_on = r_agraph_get_node (g, title);
			if (g->update_seek_on) {
				r_agraph_set_curnode (g, g->update_seek_on);
				g->force_update_seek = true;
			}
		}
		free (title);
		g->can->color = r_config_get_i (core->config, "scr.color");
		g->hints = r_config_get_i (core->config, "graph.hints");
	}
	if (g->update_seek_on || g->force_update_seek) {
		RANode *n = g->update_seek_on;
		if (!n && g->curnode) {
			n = get_anode (g->curnode);
		}
		if (n) {
			update_seek (g->can, n, g->force_update_seek);
		}
	}
	if (oldpos[0] || oldpos[1]) {
		g->can->sx = oldpos[0];
		g->can->sy = oldpos[1];
	}
	g->need_reload_nodes = false;
	g->need_update_dim = false;
	g->need_set_layout = false;
	g->update_seek_on = NULL;
	g->force_update_seek = false;
	return true;
}