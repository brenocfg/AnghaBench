#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_4__* panels; } ;
struct TYPE_17__ {TYPE_3__* view; TYPE_1__* model; } ;
struct TYPE_16__ {int n_panels; } ;
struct TYPE_14__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_15__ {TYPE_2__ pos; } ;
struct TYPE_13__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  title; } ;
typedef  TYPE_4__ RPanels ;
typedef  TYPE_5__ RPanel ;
typedef  TYPE_6__ RCore ;
typedef  int /*<<< orphan*/  PJ ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ R_STR_ISEMPTY (char const*) ; 
 char* __create_panels_config_path (char const*) ; 
 TYPE_5__* __get_panel (TYPE_4__*,int) ; 
 int /*<<< orphan*/  __init_menu_saved_layout ; 
 int /*<<< orphan*/  __show_status (TYPE_6__*,char*) ; 
 char* __show_status_input (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  __update_menu (TYPE_6__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* pj_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pj_kn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pj_ks (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pj_new () ; 
 int /*<<< orphan*/  pj_o (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_sandbox_fopen (char*,char*) ; 

void r_save_panels_layout(RCore *core) {
	int i;
	if (!core->panels) {
		return;
	}
	const char *name = __show_status_input (core, "Name for the layout: ");
	if (R_STR_ISEMPTY (name)) {
		(void)__show_status (core, "Name can't be empty!");
		return;
	}
	char *config_path = __create_panels_config_path (name);
	RPanels *panels = core->panels;
	PJ *pj = pj_new ();
	for (i = 0; i < panels->n_panels; i++) {
		RPanel *panel = __get_panel (panels, i);
		pj_o (pj);
		pj_ks (pj, "Title", panel->model->title);
		pj_ks (pj, "Cmd", panel->model->cmd);
		pj_kn (pj, "x", panel->view->pos.x);
		pj_kn (pj, "y", panel->view->pos.y);
		pj_kn (pj, "w", panel->view->pos.w);
		pj_kn (pj, "h", panel->view->pos.h);
		pj_end (pj);
	}
	FILE *fd = r_sandbox_fopen (config_path, "w");
	if (fd) {
		char *pjs = pj_drain (pj);
		fprintf (fd, "%s\n", pjs);
		free (pjs);
		fclose (fd);
		__update_menu (core, "File.Load Layout.Saved", __init_menu_saved_layout);
		(void)__show_status (core, "Panels layout saved!");
	}
	free (config_path);
}