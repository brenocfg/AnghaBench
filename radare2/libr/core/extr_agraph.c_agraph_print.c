#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int sx; int sy; } ;
struct TYPE_16__ {int h; int w; int x; int y; char* title; TYPE_6__* can; int /*<<< orphan*/  is_tiny; scalar_t__ is_dis; } ;
struct TYPE_15__ {scalar_t__ scr_gadgets; int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;
typedef  int /*<<< orphan*/  RAnalFunction ;
typedef  TYPE_2__ RAGraph ;

/* Variables and functions */
 int /*<<< orphan*/  Color_RESET ; 
 int /*<<< orphan*/  G (int,int) ; 
 int /*<<< orphan*/  W (char*) ; 
 int /*<<< orphan*/  agraph_print_edges (TYPE_2__*) ; 
 int /*<<< orphan*/  agraph_print_nodes (TYPE_2__*) ; 
 int check_changes (TYPE_2__*,int,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  r_cons_canvas_fill (TYPE_6__*,int,int,int,int,char) ; 
 int /*<<< orphan*/  r_cons_canvas_print_region (TYPE_6__*) ; 
 int /*<<< orphan*/  r_cons_canvas_resize (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  r_cons_clear00 () ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 int r_cons_get_size (int*) ; 
 int /*<<< orphan*/  r_cons_gotoxy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_cons_newline () ; 
 int /*<<< orphan*/  r_cons_strcat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_cons_visual_flush () ; 
 int /*<<< orphan*/  r_core_cmd0 (TYPE_1__*,char const*) ; 
 char* r_core_cmd_str (TYPE_1__*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  update_graph_sizes (TYPE_2__*) ; 

__attribute__((used)) static int agraph_print(RAGraph *g, int is_interactive, RCore *core, RAnalFunction *fcn) {
	int h, w = r_cons_get_size (&h);
	int ret = check_changes (g, is_interactive, core, fcn);
	if (!ret) {
		return false;
	}

	if (is_interactive) {
		r_cons_clear00 ();
	} else {
		/* TODO: limit to screen size when the output is not redirected to file */
		update_graph_sizes (g);
	}

	h = is_interactive? h: g->h + 1;
	w = is_interactive? w: g->w + 2;
	if (!r_cons_canvas_resize (g->can, w, h)) {
		return false;
	}
	// r_cons_canvas_clear (g->can);
	if (!is_interactive) {
		g->can->sx = -g->x;
		g->can->sy = -g->y - 1;
	}
	if (g->is_dis) {
		(void) G (-g->can->sx + 1, -g->can->sy + 2);
		int scr_utf8 = r_config_get_i (core->config, "scr.utf8");
		int asm_bytes = r_config_get_i (core->config, "asm.bytes");
		int asm_cmt_right = r_config_get_i (core->config, "asm.cmt.right");
		r_config_set_i (core->config, "scr.utf8", 0);
		r_config_set_i (core->config, "asm.bytes", 0);
		r_config_set_i (core->config, "asm.cmt.right", 0);
		char *str = r_core_cmd_str (core, "pd $r");
		if (str) {
			W (str);
			free (str);
		}
		r_config_set_i (core->config, "scr.utf8", scr_utf8);
		r_config_set_i (core->config, "asm.bytes", asm_bytes);
		r_config_set_i (core->config, "asm.cmt.right", asm_cmt_right);
	}
	if (g->title && *g->title) {
		g->can->sy ++;
	}
	agraph_print_edges (g);
	agraph_print_nodes (g);
	if (g->title && *g->title) {
		g->can->sy --;
	}
	/* print the graph title */
	(void) G (-g->can->sx, -g->can->sy);
	if (!g->is_tiny) {
                W (g->title);
	}
	if (is_interactive && g->title) {
		int title_len = strlen (g->title);
		r_cons_canvas_fill (g->can, -g->can->sx + title_len, -g->can->sy,
			w - title_len, 1, ' ');
	}

	r_cons_canvas_print_region (g->can);

	if (is_interactive) {
		r_cons_newline ();
		const char *cmdv = r_config_get (core->config, "cmd.gprompt");
		bool mustFlush = false;
		r_cons_visual_flush ();
		if (cmdv && *cmdv) {
			r_cons_gotoxy (0, 2);
			r_cons_strcat (Color_RESET);
			r_core_cmd0 (core, cmdv);
			mustFlush = true;
		}
		if (core && core->scr_gadgets) {
			r_core_cmd0 (core, "pg");
		}
		if (mustFlush) {
			r_cons_flush ();
		}
	}
	return true;
}