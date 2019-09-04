#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_3__* panels; } ;
struct TYPE_15__ {TYPE_2__* view; TYPE_1__* model; } ;
struct TYPE_14__ {scalar_t__ mode; int curnode; int n_panels; scalar_t__ fun; } ;
struct TYPE_13__ {int refresh; } ;
struct TYPE_12__ {int /*<<< orphan*/  cmd; } ;
typedef  TYPE_3__ RPanels ;
typedef  TYPE_4__ RPanel ;
typedef  TYPE_5__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 scalar_t__ PANEL_FUN_SAKURA ; 
 scalar_t__ PANEL_FUN_SNOW ; 
 int /*<<< orphan*/  PANEL_MODE_DEFAULT ; 
 scalar_t__ PANEL_MODE_MENU ; 
 scalar_t__ PANEL_MODE_ZOOM ; 
 TYPE_4__* getCurPanel (TYPE_3__*) ; 
 int /*<<< orphan*/  r_cons_switchbuf (int) ; 
 int /*<<< orphan*/  resetSnow (TYPE_3__*) ; 
 int /*<<< orphan*/  setMode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_3__*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handleTabKey(RCore *core, bool shift) {
	RPanels *panels = core->panels;
	RPanel *cur = getCurPanel (panels);
	r_cons_switchbuf (false);
	cur->view->refresh = true;
	if (!shift) {
		if (panels->mode == PANEL_MODE_MENU) {
			panels->curnode = 0;
			setMode (panels, PANEL_MODE_DEFAULT);
		} else if (panels->mode == PANEL_MODE_ZOOM) {
			if (panels->curnode == panels->n_panels - 1) {
				panels->curnode = 0;
			} else {
				panels->curnode++;
			}
		} else {
			if (panels->curnode == panels->n_panels - 1) {
				panels->curnode = 0;
			} else {
				panels->curnode++;
			}
		}
	} else {
		if (panels->mode == PANEL_MODE_MENU) {
			panels->curnode = panels->n_panels - 1;
			setMode (panels, PANEL_MODE_DEFAULT);
		} else if (panels->mode == PANEL_MODE_ZOOM) {
			if (panels->curnode) {
				panels->curnode--;
			} else {
				panels->curnode = panels->n_panels - 1;
			}
		} else {
			if (panels->curnode) {
				panels->curnode--;
			} else {
				panels->curnode = panels->n_panels - 1;
			}
		}
	}
	cur = getCurPanel (panels);
	if (!strncmp (cur->model->cmd, PANEL_CMD_DISASSEMBLY, strlen (PANEL_CMD_DISASSEMBLY)) &&
				strcmp (cur->model->cmd, "pdc")) {
		setRefreshAll (panels, false);
		return;
	}
	cur->view->refresh = true;
	if (panels->fun == PANEL_FUN_SNOW || panels->fun == PANEL_FUN_SAKURA) {
		resetSnow (panels);
	}
}