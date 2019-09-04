#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  offset; TYPE_2__* panels; } ;
struct TYPE_14__ {TYPE_1__* model; } ;
struct TYPE_13__ {int n_panels; } ;
struct TYPE_12__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_2__ RPanels ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 TYPE_3__* getCurPanel (TYPE_2__*) ; 
 TYPE_3__* getPanel (TYPE_2__*,int) ; 
 int /*<<< orphan*/  r_core_visual_hudstuff (TYPE_4__*) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_2__*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hudstuff(RCore *core) {
	RPanels *panels = core->panels;
	RPanel *cur = getCurPanel (panels);
	r_core_visual_hudstuff (core);

	if (!strncmp (cur->model->cmd, PANEL_CMD_DISASSEMBLY, strlen (PANEL_CMD_DISASSEMBLY)) &&
				strcmp (cur->model->cmd, "pdc")) {
		cur->model->addr = core->offset;
	} else {
		int i;
		for (i = 0; i < panels->n_panels; i++) {
			RPanel *panel = getPanel (panels, i);
			if (!strncmp (cur->model->cmd, PANEL_CMD_DISASSEMBLY, strlen (PANEL_CMD_DISASSEMBLY)) &&
						strcmp (cur->model->cmd, "pdc")) {
				panel->model->addr = core->offset;
				break;
			}
		}
	}
	setRefreshAll (panels, true);
}