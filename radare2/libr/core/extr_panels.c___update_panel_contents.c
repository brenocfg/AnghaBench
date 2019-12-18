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
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_4__* panels; TYPE_1__* print; } ;
struct TYPE_16__ {TYPE_3__* view; } ;
struct TYPE_15__ {int /*<<< orphan*/ * can; } ;
struct TYPE_13__ {int x; int y; int w; int h; } ;
struct TYPE_14__ {int sx; int sy; int curpos; TYPE_2__ pos; } ;
struct TYPE_12__ {scalar_t__ cur_enabled; } ;
typedef  TYPE_4__ RPanels ;
typedef  TYPE_5__ RPanel ;
typedef  TYPE_6__ RCore ;
typedef  int /*<<< orphan*/  RConsCanvas ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_GRAPH ; 
 int R_MAX (int,int /*<<< orphan*/ ) ; 
 int R_MIN (int,scalar_t__) ; 
 scalar_t__ __check_panel_type (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ __is_abnormal_cursor_type (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_canvas_gotoxy (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  r_cons_canvas_write (int /*<<< orphan*/ *,char*) ; 
 char* r_str_ansi_crop (char const*,int,int,int,int) ; 
 scalar_t__ r_str_pad (char,int) ; 
 char* r_str_prefix_all (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

void __update_panel_contents(RCore *core, RPanel *panel, const char *cmdstr) {
	bool b = __is_abnormal_cursor_type (core, panel) && core->print->cur_enabled;
	int sx = b ? -2 :panel->view->sx;
	int sy = R_MAX (panel->view->sy, 0);
	int x = panel->view->pos.x;
	int y = panel->view->pos.y;
	int w = panel->view->pos.w;
	int h = panel->view->pos.h;
	int graph_pad = __check_panel_type (panel, PANEL_CMD_GRAPH) ? 1 : 0;
	char *text = NULL;
	RPanels *panels = core->panels;
	RConsCanvas *can = panels->can;
	(void) r_cons_canvas_gotoxy (can, x + 2, y + 2);
	if (sx < 0) {
		char *white = (char*)r_str_pad (' ', 128);
		int idx = R_MIN (-sx, strlen (white) - 1);
		white[idx] = 0;
		text = r_str_ansi_crop (cmdstr,
				0, sy + graph_pad, w + sx - 3, h - 2 + sy);
		char *newText = r_str_prefix_all (text, white);
		if (newText) {
			free (text);
			text = newText;
		}
	} else {
		text = r_str_ansi_crop (cmdstr,
				sx, sy + graph_pad, w + sx - 3, h - 2 + sy);
	}
	if (text) {
		r_cons_canvas_write (can, text);
		free (text);
	}
	if (b) {
		int sub = panel->view->curpos - panel->view->sy;
		(void) r_cons_canvas_gotoxy (can, panel->view->pos.x + 2, panel->view->pos.y + 2 + sub);
		r_cons_canvas_write (can, "*");
	}
}