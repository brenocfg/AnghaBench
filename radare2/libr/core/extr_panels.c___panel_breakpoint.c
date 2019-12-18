#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  panels; } ;
struct TYPE_9__ {TYPE_1__* view; } ;
struct TYPE_8__ {int refresh; } ;
typedef  TYPE_2__ RPanel ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 scalar_t__ __check_panel_type (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* __get_cur_panel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_cmd (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 

void __panel_breakpoint(RCore *core) {
	RPanel *cur = __get_cur_panel (core->panels);
	if (__check_panel_type (cur, PANEL_CMD_DISASSEMBLY)) {
		r_core_cmd (core, "dbs $$", 0);
		cur->view->refresh = true;
	}
}