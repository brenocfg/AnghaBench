#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_4__* panels; } ;
struct TYPE_13__ {TYPE_3__* view; TYPE_1__* model; } ;
struct TYPE_12__ {int /*<<< orphan*/ * can; } ;
struct TYPE_10__ {int x; int y; int w; int h; } ;
struct TYPE_11__ {int sx; TYPE_2__ pos; int /*<<< orphan*/  sy; } ;
struct TYPE_9__ {char* readOnly; } ;
typedef  TYPE_4__ RPanels ;
typedef  TYPE_5__ RPanel ;
typedef  TYPE_6__ RCore ;
typedef  int /*<<< orphan*/  RConsCanvas ;

/* Variables and functions */
 int R_MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int R_MIN (int,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_canvas_gotoxy (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  r_cons_canvas_write (int /*<<< orphan*/ *,char*) ; 
 char* r_str_ansi_crop (char*,int,int,int,int) ; 
 scalar_t__ r_str_pad (char,int) ; 
 char* r_str_prefix_all (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

void __update_help_contents(RCore *core, RPanel *panel) {
	char *read_only = panel->model->readOnly;
	char *text = NULL;
	int sx = panel->view->sx;
	int sy = R_MAX (panel->view->sy, 0);
	int x = panel->view->pos.x;
	int y = panel->view->pos.y;
	int w = panel->view->pos.w;
	int h = panel->view->pos.h;
	RPanels *panels = core->panels;
	RConsCanvas *can = panels->can;
	(void) r_cons_canvas_gotoxy (can, x + 2, y + 2);
	if (sx < 0) {
		char *white = (char*)r_str_pad (' ', 128);
		int idx = R_MIN (-sx, strlen (white) - 1);
		white[idx] = 0;
		text = r_str_ansi_crop (read_only,
				0, sy, w + sx - 3, h - 2 + sy);
		char *newText = r_str_prefix_all (text, white);
		if (newText) {
			free (text);
			text = newText;
		}
	} else {
		text = r_str_ansi_crop (read_only,
				sx, sy, w + sx - 3, h - 2 + sy);
	}
	if (text) {
		r_cons_canvas_write (can, text);
		free (text);
	}
}