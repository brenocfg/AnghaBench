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
 int /*<<< orphan*/  __add_help_panel (TYPE_4__*) ; 
 int /*<<< orphan*/  __dismantle_del_panel (TYPE_4__*,TYPE_3__*,int) ; 
 TYPE_3__* __get_panel (TYPE_2__*,int) ; 
 int /*<<< orphan*/  __set_mode (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  __update_help (TYPE_2__*) ; 
 scalar_t__ r_str_endswith (int /*<<< orphan*/ ,char*) ; 

void __toggle_help(RCore *core) {
	RPanels *ps = core->panels;
	int i;
	for (i = 0; i < ps->n_panels; i++) {
		RPanel *p = __get_panel (ps, i);
		if (r_str_endswith (p->model->cmd, "Help")) {
			__dismantle_del_panel (core, p, i);
			if (ps->mode == PANEL_MODE_MENU) {
				__set_mode (core, PANEL_MODE_DEFAULT);
			}
			__set_refresh_all (core, false, false);
			return;
		}
	}
	__add_help_panel (core);
	if (ps->mode == PANEL_MODE_MENU) {
		__set_mode (core, PANEL_MODE_DEFAULT);
	}
	__update_help (ps);
}