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
struct TYPE_14__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  io; int /*<<< orphan*/  panels; } ;
struct TYPE_13__ {int /*<<< orphan*/  off; } ;
struct TYPE_12__ {TYPE_1__* view; TYPE_2__* model; } ;
struct TYPE_11__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  cmd; } ;
struct TYPE_10__ {int refresh; } ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RIOUndos ;
typedef  TYPE_5__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 TYPE_3__* getCurPanel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_visual_seek_animation (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* r_io_sundo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void undoSeek(RCore *core) {
	RPanel *cur = getCurPanel (core->panels);
	if (!strncmp (cur->model->cmd, PANEL_CMD_DISASSEMBLY, strlen (PANEL_CMD_DISASSEMBLY)) &&
				strcmp (cur->model->cmd, "pdc")) {
		return;
	}
	RIOUndos *undo = r_io_sundo (core->io, core->offset);
	if (undo) {
		r_core_visual_seek_animation (core, undo->off);
		cur->model->addr = core->offset;
		cur->view->refresh = true;
	}
}