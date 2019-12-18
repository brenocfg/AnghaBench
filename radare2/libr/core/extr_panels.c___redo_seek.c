#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  io; int /*<<< orphan*/  panels; } ;
struct TYPE_7__ {int /*<<< orphan*/  off; } ;
typedef  int /*<<< orphan*/  RPanel ;
typedef  TYPE_1__ RIOUndos ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 int /*<<< orphan*/  __check_panel_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * __get_cur_panel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_panel_addr (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_visual_seek_animation (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* r_io_sundo_redo (int /*<<< orphan*/ ) ; 

void __redo_seek(RCore *core) {
	RPanel *cur = __get_cur_panel (core->panels);
	if (!__check_panel_type (cur, PANEL_CMD_DISASSEMBLY)) {
		return;
	}
	RIOUndos *undo = r_io_sundo_redo (core->io);
	if (undo) {
		r_core_visual_seek_animation (core, undo->off);
		__set_panel_addr (core, cur, core->offset);
	}
}