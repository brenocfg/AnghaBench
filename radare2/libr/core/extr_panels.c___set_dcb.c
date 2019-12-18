#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* model; } ;
struct TYPE_6__ {void* directionCb; scalar_t__ readOnly; scalar_t__ cmdStrCache; scalar_t__ cache; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_2__ RPanel ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 int /*<<< orphan*/  PANEL_CMD_GRAPH ; 
 int /*<<< orphan*/  PANEL_CMD_HEXDUMP ; 
 int /*<<< orphan*/  PANEL_CMD_REGISTERS ; 
 int /*<<< orphan*/  PANEL_CMD_STACK ; 
 scalar_t__ __check_panel_type (TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* __direction_default_cb ; 
 void* __direction_disassembly_cb ; 
 void* __direction_graph_cb ; 
 void* __direction_hexdump_cb ; 
 void* __direction_panels_cursor_cb ; 
 void* __direction_register_cb ; 
 void* __direction_stack_cb ; 
 scalar_t__ __is_abnormal_cursor_type (int /*<<< orphan*/ *,TYPE_2__*) ; 

void __set_dcb(RCore *core, RPanel *p) {
	if (!p->model->cmd) {
		return;
	}
	if (__check_panel_type (p, PANEL_CMD_GRAPH)) {
		p->model->directionCb = __direction_graph_cb;
		return;
	}
	if ((p->model->cache && p->model->cmdStrCache) || p->model->readOnly) {
		p->model->directionCb = __direction_default_cb;
		return;
	}
	if (__check_panel_type (p, PANEL_CMD_STACK)) {
		p->model->directionCb = __direction_stack_cb;
	} else if (__check_panel_type (p, PANEL_CMD_DISASSEMBLY)) {
		p->model->directionCb = __direction_disassembly_cb;
	} else if (__check_panel_type (p, PANEL_CMD_REGISTERS)) {
		p->model->directionCb = __direction_register_cb;
	} else if (__check_panel_type (p, PANEL_CMD_HEXDUMP)) {
		p->model->directionCb = __direction_hexdump_cb;
	} else if (__is_abnormal_cursor_type (core, p)) {
		p->model->directionCb = __direction_panels_cursor_cb;
	} else {
		p->model->directionCb = __direction_default_cb;
	}
}