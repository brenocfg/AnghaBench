#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* print; int /*<<< orphan*/ * panels; } ;
struct TYPE_13__ {TYPE_3__* view; TYPE_1__* model; } ;
struct TYPE_12__ {int refresh; } ;
struct TYPE_11__ {int /*<<< orphan*/  cur_enabled; } ;
struct TYPE_10__ {int cache; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  RPanels ;
typedef  TYPE_4__ RPanel ;
typedef  TYPE_5__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 int /*<<< orphan*/  PANEL_CMD_HEXDUMP ; 
 int /*<<< orphan*/  PANEL_CMD_REGISTERS ; 
 int /*<<< orphan*/  PANEL_CMD_STACK ; 
 TYPE_4__* getCurPanel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_any_key (char*) ; 
 scalar_t__ r_cons_yesno (char,char*) ; 
 int /*<<< orphan*/  setCmdStrCache (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setCursor (TYPE_5__*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void activateCursor(RCore *core) {
	RPanels *panels = core->panels;
	RPanel *cur = getCurPanel (panels);
	if (!strncmp (cur->model->cmd, PANEL_CMD_STACK, strlen (PANEL_CMD_STACK))
			|| !strncmp (cur->model->cmd, PANEL_CMD_REGISTERS, strlen (PANEL_CMD_REGISTERS))
			|| (!strncmp (cur->model->cmd, PANEL_CMD_DISASSEMBLY, strlen (PANEL_CMD_DISASSEMBLY)) &&
					strcmp (cur->model->cmd, "pdc"))
			|| !strncmp (cur->model->cmd, PANEL_CMD_HEXDUMP, strlen (PANEL_CMD_HEXDUMP))) {
		if (cur->model->cache) {
			if (r_cons_yesno ('y', "You need to turn off cache to use cursor. Turn off now?(Y/n)")) {
				cur->model->cache = false;
				setCmdStrCache (cur, NULL);
				cur->view->refresh = true;
				(void)r_cons_any_key ("Cache is off and cursor is on");
				setCursor (core, !core->print->cur_enabled);
				cur->view->refresh = true;
			} else {
				(void)r_cons_any_key ("You can always toggle cache by \'&\' key");
			}
			return;
		}
		setCursor (core, !core->print->cur_enabled);
		cur->view->refresh = true;
	} else {
		(void)r_cons_any_key ("Cursor is not available for the current panel.");
	}
}