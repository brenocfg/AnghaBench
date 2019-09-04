#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  offset; TYPE_2__* print; int /*<<< orphan*/ * panels; } ;
struct TYPE_19__ {TYPE_3__* model; TYPE_1__* view; } ;
struct TYPE_18__ {int /*<<< orphan*/  addr; } ;
struct TYPE_17__ {int cols; int /*<<< orphan*/  cur_enabled; } ;
struct TYPE_16__ {int refresh; int /*<<< orphan*/  sx; } ;
typedef  int /*<<< orphan*/  RPanels ;
typedef  TYPE_4__ RPanel ;
typedef  TYPE_5__ RCore ;
typedef  int /*<<< orphan*/  RAsmOp ;
typedef  int /*<<< orphan*/  Direction ;

/* Variables and functions */
#define  DOWN 131 
#define  LEFT 130 
#define  RIGHT 129 
#define  UP 128 
 int /*<<< orphan*/  cursorDown (TYPE_5__*) ; 
 int /*<<< orphan*/  cursorLeft (TYPE_5__*) ; 
 int /*<<< orphan*/  cursorRight (TYPE_5__*) ; 
 int /*<<< orphan*/  cursorUp (TYPE_5__*) ; 
 TYPE_4__* getCurPanel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_core_block_read (TYPE_5__*) ; 
 int /*<<< orphan*/  r_core_seek (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_core_seek_delta (TYPE_5__*,int) ; 
 int /*<<< orphan*/  r_core_visual_disasm_down (TYPE_5__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  r_core_visual_disasm_up (TYPE_5__*,int*) ; 

__attribute__((used)) static void directionDisassemblyCb(void *user, int direction) {
	RCore *core = (RCore *)user;
	RPanels *panels = core->panels;
	RPanel *cur = getCurPanel (panels);
	int cols = core->print->cols;
	cur->view->refresh = true;
	switch ((Direction)direction) {
	case LEFT:
		if (core->print->cur_enabled) {
			cursorLeft (core);
		} else if (cur->view->sx > 0) {
			cur->view->sx--;
			cur->view->refresh = true;
		}
		return;
	case RIGHT:
		if (core->print->cur_enabled) {
			cursorRight (core);
		} else {
			cur->view->sx++;
			cur->view->refresh = true;
		}
		return;
	case UP:
		core->offset = cur->model->addr;
		if (core->print->cur_enabled) {
			cursorUp (core);
			cur->model->addr = core->offset;
		} else {
			r_core_visual_disasm_up (core, &cols);
			r_core_seek_delta (core, -cols);
			cur->model->addr = core->offset;
		}
		return;
	case DOWN:
		core->offset = cur->model->addr;
		if (core->print->cur_enabled) {
			cursorDown (core);
			r_core_block_read (core);
			cur->model->addr = core->offset;
		} else {
			RAsmOp op;
			r_core_visual_disasm_down (core, &op, &cols);
			r_core_seek (core, core->offset + cols, 1);
			r_core_block_read (core);
			cur->model->addr = core->offset;
		}
		return;
	}
}