#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  config; } ;
struct TYPE_8__ {TYPE_1__* model; } ;
struct TYPE_7__ {char* cmd; } ;
typedef  TYPE_2__ RPanel ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_STACK ; 
 int R_ABS (int const) ; 
 int /*<<< orphan*/  __update_panel_contents (TYPE_3__*,TYPE_2__*,char const*) ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 char* r_core_cmd_str (TYPE_3__*,char*) ; 
 char* r_str_append (char*,char const*) ; 
 char* r_str_newf (char*,char*,...) ; 
 int r_str_split (char*,char) ; 
 char* r_str_word_get0 (char*,int) ; 

void __print_stack_cb(void *user, void *p) {
	RCore *core = (RCore *)user;
	RPanel *panel = (RPanel *)p;
	const int delta = r_config_get_i (core->config, "stack.delta");
	const int bits = r_config_get_i (core->config, "asm.bits");
	const char sign = (delta < 0)? '+': '-';
	const int absdelta = R_ABS (delta);
	char *cmd = r_str_newf ("%s%s ", PANEL_CMD_STACK, bits == 32 ? "w" : "q");
	int n = r_str_split (panel->model->cmd, ' ');
	int i;
	for (i = 0; i < n; i++) {
		const char *s = r_str_word_get0 (panel->model->cmd, i);
		if (!i) {
			continue;
		}
		cmd = r_str_append (cmd, s);
	}
	panel->model->cmd = cmd;
	const char *cmdstr = r_core_cmd_str (core, r_str_newf ("%s%c%d", cmd, sign, absdelta));
	__update_panel_contents (core, panel, cmdstr);
}