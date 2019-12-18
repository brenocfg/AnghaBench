#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_2__* print; int /*<<< orphan*/  panels; } ;
struct TYPE_15__ {TYPE_1__* model; } ;
struct TYPE_14__ {int cur_enabled; } ;
struct TYPE_13__ {int cache; } ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (char*) ; 
 scalar_t__ R_STR_ISNOTEMPTY (char*) ; 
 char* __apply_filter_cmd (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* __get_cur_panel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_cmd_str_cache (TYPE_4__*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_echo (int /*<<< orphan*/ *) ; 
 char* r_core_cmd_str (TYPE_4__*,char*) ; 

char *__handle_cmd_str_cache(RCore *core, RPanel *panel, bool force_cache) {
	char *cmd = __apply_filter_cmd (core, panel);
	bool b = core->print->cur_enabled && __get_cur_panel (core->panels) != panel;
	if (b) {
		core->print->cur_enabled = false;
	}
	char *out = r_core_cmd_str (core, cmd);
	r_cons_echo (NULL);
	if (force_cache) {
		panel->model->cache = true;
	}
	if (R_STR_ISNOTEMPTY (out)) {
		__set_cmd_str_cache (core, panel, out);
	} else {
		R_FREE (out);
	}
	free (cmd);
	if (b) {
		core->print->cur_enabled = true;
	}
	return out;
}