#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  offset; } ;
struct TYPE_13__ {TYPE_1__* model; } ;
struct TYPE_12__ {int n_panels; } ;
struct TYPE_11__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_2__ RPanels ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 TYPE_3__* getPanel (TYPE_2__*,int) ; 
 int /*<<< orphan*/  r_core_visual_prompt_input (TYPE_4__*) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_2__*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handlePrompt(RCore *core, RPanels *panels) {
	r_core_visual_prompt_input (core);
	int i;
	for (i = 0; i < panels->n_panels; i++) {
		RPanel *p = getPanel (panels, i);
		if (!strncmp (p->model->cmd, PANEL_CMD_DISASSEMBLY, strlen (PANEL_CMD_DISASSEMBLY)) &&
					strcmp (p->model->cmd, "pdc")) {
			p->model->addr = core->offset;
			break;
		}
	}
	setRefreshAll (panels, false);
}