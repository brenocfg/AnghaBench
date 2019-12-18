#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_2__* print; int /*<<< orphan*/  panels; } ;
struct TYPE_18__ {TYPE_1__* model; } ;
struct TYPE_17__ {int cur_enabled; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* print_cb ) (TYPE_4__*,TYPE_3__*) ;scalar_t__ cmd; scalar_t__ readOnly; } ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 TYPE_3__* __get_cur_panel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __update_help_contents (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  __update_help_title (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  __update_panel_title (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,TYPE_3__*) ; 

void __default_panel_print(RCore *core, RPanel *panel) {
	bool o_cur = core->print->cur_enabled;
	core->print->cur_enabled = o_cur & (__get_cur_panel (core->panels) == panel);
	if (panel->model->readOnly) {
		__update_help_contents (core, panel);
		__update_help_title (core, panel);
	} else if (panel->model->cmd) {
		panel->model->print_cb (core, panel);
		__update_panel_title (core, panel);
	}
	core->print->cur_enabled = o_cur;
}