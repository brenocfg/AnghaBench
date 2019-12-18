#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  addr; } ;
struct TYPE_19__ {TYPE_3__* panels_root; int /*<<< orphan*/  config; int /*<<< orphan*/  offset; int /*<<< orphan*/  anal; TYPE_5__* panels; } ;
struct TYPE_18__ {TYPE_4__* model; TYPE_2__* view; } ;
struct TYPE_17__ {int /*<<< orphan*/ * can; } ;
struct TYPE_16__ {scalar_t__ cmdStrCache; } ;
struct TYPE_15__ {int /*<<< orphan*/ * pdc_caches; int /*<<< orphan*/ * cur_pdc_cache; } ;
struct TYPE_13__ {int x; int y; int w; int h; } ;
struct TYPE_14__ {int sx; TYPE_1__ pos; int /*<<< orphan*/  sy; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  TYPE_5__ RPanels ;
typedef  TYPE_6__ RPanel ;
typedef  TYPE_7__ RCore ;
typedef  int /*<<< orphan*/  RConsCanvas ;
typedef  TYPE_8__ RAnalFunction ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_FCN_TYPE_NULL ; 
 int R_MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int R_MIN (int,scalar_t__) ; 
 int /*<<< orphan*/  __reset_scroll_pos (TYPE_6__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_8__* r_anal_get_fcn_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_cons_canvas_gotoxy (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  r_cons_canvas_write (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * r_num_as_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* r_str_ansi_crop (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/ * r_str_new (char const*) ; 
 scalar_t__ r_str_pad (char,int) ; 
 char* r_str_prefix_all (char*,char*) ; 
 int /*<<< orphan*/  sdb_exists (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * sdb_new0 () ; 
 int /*<<< orphan*/  sdb_ptr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

void __update_pdc_contents(RCore *core, RPanel *panel, char *cmdstr) {
	RPanels *panels = core->panels;
	RConsCanvas *can = panels->can;
	RAnalFunction *func = r_anal_get_fcn_in (core->anal, core->offset, R_ANAL_FCN_TYPE_NULL);
	int sx = panel->view->sx;
	int sy = R_MAX (panel->view->sy, 0);
	int x = panel->view->pos.x;
	int y = panel->view->pos.y;
	int w = panel->view->pos.w;
	int h = panel->view->pos.h;
	char *text = NULL;

	if (func) {
		if (core->panels_root->cur_pdc_cache) {
			sdb_ptr_set (core->panels_root->cur_pdc_cache, r_num_as_string (NULL, func->addr, false), r_str_new (cmdstr), 0);
		} else {
			Sdb *sdb = sdb_new0 ();
			const char *pdc_now = r_config_get (core->config, "cmd.pdc");
			sdb_ptr_set (sdb, r_num_as_string (NULL, func->addr, false), r_str_new (cmdstr), 0);
			core->panels_root->cur_pdc_cache = sdb;
			if (!sdb_exists (core->panels_root->pdc_caches, pdc_now)) {
				sdb_ptr_set (core->panels_root->pdc_caches, r_str_new (pdc_now), sdb, 0);
			}
		}
	}

	if (panel->model->cmdStrCache) {
		__reset_scroll_pos (panel);
	}

	(void) r_cons_canvas_gotoxy (can, x + 2, y + 2);

	if (sx < 0) {
		char *white = (char*)r_str_pad (' ', 128);
		int idx = R_MIN (-sx, strlen (white) - 1);
		white[idx] = 0;
		text = r_str_ansi_crop (r_str_new (cmdstr),
				0, sy, w + sx - 3, h - 2 + sy);
		char *newText = r_str_prefix_all (text, white);
		if (newText) {
			free (text);
			text = newText;
		}
	} else {
		text = r_str_ansi_crop (r_str_new (cmdstr),
				sx, sy, w + sx - 3, h - 2 + sy);
	}
	if (text) {
		r_cons_canvas_write (can, text);
		free (text);
	}
}