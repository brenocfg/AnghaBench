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
struct TYPE_14__ {int /*<<< orphan*/  addr; } ;
struct TYPE_13__ {TYPE_2__* panels; TYPE_1__* panels_root; int /*<<< orphan*/  offset; int /*<<< orphan*/  anal; } ;
struct TYPE_12__ {scalar_t__ autoUpdate; } ;
struct TYPE_11__ {scalar_t__ cur_pdc_cache; } ;
typedef  int /*<<< orphan*/  RPanel ;
typedef  TYPE_3__ RCore ;
typedef  TYPE_4__ RAnalFunction ;

/* Variables and functions */
 int /*<<< orphan*/  R_ANAL_FCN_TYPE_NULL ; 
 scalar_t__ __check_func_diff (TYPE_3__*,int /*<<< orphan*/ *) ; 
 char* __find_cmd_str_cache (TYPE_3__*,int /*<<< orphan*/ *) ; 
 char* __handle_cmd_str_cache (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __update_panel_contents (TYPE_3__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  __update_pdc_contents (TYPE_3__*,int /*<<< orphan*/ *,char*) ; 
 TYPE_4__* r_anal_get_fcn_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_num_as_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* r_str_new (char*) ; 
 scalar_t__ sdb_ptr_get (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void __print_decompiler_cb(void *user, void *p) {
	//TODO: Refactoring
	//TODO: Also, __check_func_diff should use addr not name
	RCore *core = (RCore *)user;
	RPanel *panel = (RPanel *)p;
	RAnalFunction *func = r_anal_get_fcn_in (core->anal, core->offset, R_ANAL_FCN_TYPE_NULL);
	char *cmdstr = NULL;
	if (func && core->panels_root->cur_pdc_cache) {
		cmdstr = r_str_new ((char *)sdb_ptr_get (core->panels_root->cur_pdc_cache,
					r_num_as_string (NULL, func->addr, false), 0));
	}
	if (cmdstr) {
		__update_panel_contents (core, panel, cmdstr);
		return;
	}
	bool update = core->panels->autoUpdate && __check_func_diff (core, panel);
	if (update) {
		cmdstr = __handle_cmd_str_cache (core, panel, false);
		__update_pdc_contents (core, panel, cmdstr);
		return;
	}
	cmdstr = __find_cmd_str_cache (core, panel);
	if (cmdstr) {
		__update_panel_contents (core, panel, cmdstr);
	}
}