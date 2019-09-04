#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  panels; } ;
struct TYPE_10__ {TYPE_2__* view; TYPE_1__* model; } ;
struct TYPE_9__ {int refresh; } ;
struct TYPE_8__ {int /*<<< orphan*/  cmd; } ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 TYPE_3__* getCurPanel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_cmd (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void panelBreakpoint(RCore *core) {
	RPanel *cur = getCurPanel (core->panels);
	if (!strncmp (cur->model->cmd, PANEL_CMD_DISASSEMBLY, strlen (PANEL_CMD_DISASSEMBLY)) &&
				strcmp (cur->model->cmd, "pdc")) {
		r_core_cmd (core, "dbs $$", 0);
		cur->view->refresh = true;
	}
}