#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_19__ {int is_tiny; int force_update_seek; int need_set_layout; int need_update_dim; void* layout; TYPE_1__* can; } ;
struct TYPE_18__ {int /*<<< orphan*/  config; TYPE_4__* graph; int /*<<< orphan*/  offset; } ;
struct TYPE_17__ {void* color; void* linemode; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  TYPE_2__ RCore ;
typedef  int /*<<< orphan*/  RANode ;
typedef  int /*<<< orphan*/  PJ ;

/* Variables and functions */
 int /*<<< orphan*/  agraph_print_edge ; 
 int /*<<< orphan*/  agraph_print_edge_dot ; 
 int /*<<< orphan*/  agraph_print_edge_gml ; 
 int /*<<< orphan*/  agraph_print_node ; 
 int /*<<< orphan*/  agraph_print_node_dot ; 
 int /*<<< orphan*/  agraph_print_node_gml ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* graph_cmd (TYPE_2__*,char*,char const*) ; 
 int /*<<< orphan*/  pj_a (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_k (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * pj_new () ; 
 int /*<<< orphan*/  pj_o (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_agraph_foreach (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_agraph_foreach_edge (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_agraph_get_first_node (TYPE_4__*) ; 
 int /*<<< orphan*/ * r_agraph_get_sdb (TYPE_4__*) ; 
 int /*<<< orphan*/  r_agraph_print (TYPE_4__*) ; 
 int /*<<< orphan*/  r_agraph_print_json (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_agraph_set_curnode (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_agraph_set_title (TYPE_4__*,char*) ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 void* r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  r_cons_enable_mouse (int) ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 int r_cons_is_interactive () ; 
 int /*<<< orphan*/  r_cons_print (char*) ; 
 int /*<<< orphan*/  r_cons_printf (char*,...) ; 
 int /*<<< orphan*/  r_cons_println (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_cons_show_cursor (int) ; 
 int /*<<< orphan*/  r_core_cmd0 (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  r_core_seek (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_visual_graph (TYPE_2__*,TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 char* r_str_trim_ro (char const*) ; 
 char* sdb_querys (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void cmd_agraph_print(RCore *core, const char *input) {
	switch (*input) {
	case 0:
		core->graph->can->linemode = r_config_get_i (core->config, "graph.linemode");
		core->graph->can->color = r_config_get_i (core->config, "scr.color");
		r_agraph_set_title (core->graph,
			r_config_get (core->config, "graph.title"));
		r_agraph_print (core->graph);
		break;
	case 't':{ // "aggt" - tiny graph
		core->graph->is_tiny = true;
		int e = r_config_get_i (core->config, "graph.edges");
		r_config_set_i (core->config, "graph.edges", 0);
		r_core_visual_graph (core, core->graph, NULL, false);
		r_config_set_i (core->config, "graph.edges", e);
		core->graph->is_tiny = false;
		break;
		}
	case 'k': // "aggk"
	{
		Sdb *db = r_agraph_get_sdb (core->graph);
		char *o = sdb_querys (db, "null", 0, "*");
		r_cons_print (o);
		free (o);
		break;
	}
	case 'v': // "aggv"
	case 'i': // "aggi" - open current core->graph in interactive mode
	{
		RANode *ran = r_agraph_get_first_node (core->graph);
		if (ran) {
			ut64 oseek = core->offset;
			r_agraph_set_title (core->graph, r_config_get (core->config, "graph.title"));
			r_agraph_set_curnode (core->graph, ran);
			core->graph->force_update_seek = true;
			core->graph->need_set_layout = true;
			core->graph->layout = r_config_get_i (core->config, "graph.layout");
			int ov = r_cons_is_interactive ();
			core->graph->need_update_dim = true;
			r_core_visual_graph (core, core->graph, NULL, true);
			r_config_set_i (core->config, "scr.interactive", ov);
			r_cons_show_cursor (true);
			r_cons_enable_mouse (false);
			r_core_seek (core, oseek, 0);
		} else {
			eprintf ("This graph contains no nodes\n");
		}
		break;
	}
	case 'd': { // "aggd" - dot format
		const char *font = r_config_get (core->config, "graph.font");
		r_cons_printf ("digraph code {\nrankdir=LR;\noutputorder=edgesfirst\ngraph [bgcolor=azure];\n"
			"edge [arrowhead=normal, color=\"#3030c0\" style=bold weight=2];\n"
			"node [fillcolor=white, style=filled shape=box "
			"fontname=\"%s\" fontsize=\"8\"];\n", font);
		r_agraph_foreach (core->graph, agraph_print_node_dot, NULL);
		r_agraph_foreach_edge (core->graph, agraph_print_edge_dot, NULL);
		r_cons_printf ("}\n");
		break;
		}
	case '*': // "agg*" -
		r_agraph_foreach (core->graph, agraph_print_node, NULL);
		r_agraph_foreach_edge (core->graph, agraph_print_edge, NULL);
		break;
	case 'J':
	case 'j': {
		PJ *pj = pj_new ();
		if (!pj) {
			return;
		}
		pj_o (pj);
		pj_k (pj, "nodes");
		pj_a (pj);
		r_agraph_print_json (core->graph, pj);
		pj_end (pj);
		pj_end (pj);
		r_cons_println (pj_string (pj));
		pj_free (pj);
	} break;
	case 'g':
		r_cons_printf ("graph\n[\n" "hierarchic 1\n" "label \"\"\n" "directed 1\n");
		r_agraph_foreach (core->graph, agraph_print_node_gml, NULL);
		r_agraph_foreach_edge (core->graph, agraph_print_edge_gml, NULL);
		r_cons_print ("]\n");
		break;
	case 'w':{ // "aggw"
		if (r_config_get_i (core->config, "graph.web")) {
			r_core_cmd0 (core, "=H /graph/");
		} else {
			const char *filename = r_str_trim_ro (input + 1);
			char *cmd = graph_cmd (core, "aggd", filename);
			if (cmd && *cmd) {
				if (input[1] == ' ') {
					r_cons_printf ("Saving to file '%s'...\n", filename);
					r_cons_flush ();
				}
				r_core_cmd0 (core, cmd);
			}
			free (cmd);
		}
		break;
	}
	default:
		eprintf ("Usage: see ag?\n");
	}
}