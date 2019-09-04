#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_2__* panels; } ;
struct TYPE_16__ {TYPE_1__* model; } ;
struct TYPE_15__ {int n_panels; scalar_t__ mode; } ;
struct TYPE_14__ {int /*<<< orphan*/  cmd; } ;
typedef  TYPE_2__ RPanels ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_MODE_DEFAULT ; 
 scalar_t__ PANEL_MODE_MENU ; 
 int /*<<< orphan*/  addHelpPanel (TYPE_4__*) ; 
 int /*<<< orphan*/  dismantleDelPanel (TYPE_2__*,TYPE_3__*,int) ; 
 TYPE_3__* getPanel (TYPE_2__*,int) ; 
 scalar_t__ r_str_endswith (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setMode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_2__*,int) ; 
 int /*<<< orphan*/  updateHelp (TYPE_2__*) ; 

__attribute__((used)) static void toggleHelp(RCore *core) {
	RPanels *ps = core->panels;
	int i;
	for (i = 0; i < ps->n_panels; i++) {
		RPanel *p = getPanel (ps, i);
		if (r_str_endswith (p->model->cmd, "Help")) {
			dismantleDelPanel (ps, p, i);
			if (ps->mode == PANEL_MODE_MENU) {
				setMode (ps, PANEL_MODE_DEFAULT);
			}
			setRefreshAll (ps, false);
			return;
		}
	}
	addHelpPanel (core);
	if (ps->mode == PANEL_MODE_MENU) {
		setMode (ps, PANEL_MODE_DEFAULT);
	}
	updateHelp (ps);
}