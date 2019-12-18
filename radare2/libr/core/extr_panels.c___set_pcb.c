#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* model; } ;
struct TYPE_5__ {void* print_cb; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_2__ RPanel ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DECOMPILER ; 
 int /*<<< orphan*/  PANEL_CMD_DISASMSUMMARY ; 
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 int /*<<< orphan*/  PANEL_CMD_GRAPH ; 
 int /*<<< orphan*/  PANEL_CMD_HEXDUMP ; 
 int /*<<< orphan*/  PANEL_CMD_STACK ; 
 int /*<<< orphan*/  PANEL_CMD_TINYGRAPH ; 
 scalar_t__ __check_panel_type (TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* __print_decompiler_cb ; 
 void* __print_default_cb ; 
 void* __print_disasmsummary_cb ; 
 void* __print_disassembly_cb ; 
 void* __print_graph_cb ; 
 void* __print_hexdump_cb ; 
 void* __print_stack_cb ; 

void __set_pcb(RPanel *p) {
	if (!p->model->cmd) {
		return;
	}
	if (__check_panel_type (p, PANEL_CMD_DISASSEMBLY)) {
		p->model->print_cb = __print_disassembly_cb;
		return;
	}
	if (__check_panel_type (p, PANEL_CMD_STACK)) {
		p->model->print_cb = __print_stack_cb;
		return;
	}
	if (__check_panel_type (p, PANEL_CMD_HEXDUMP)) {
		p->model->print_cb = __print_hexdump_cb;
		return;
	}
	if (__check_panel_type (p, PANEL_CMD_DECOMPILER)) {
		p->model->print_cb = __print_decompiler_cb;
		return;
	}
	if (__check_panel_type (p, PANEL_CMD_GRAPH)) {
		p->model->print_cb = __print_graph_cb;
		return;
	}
	if (__check_panel_type (p, PANEL_CMD_TINYGRAPH)) {
		p->model->print_cb = __print_graph_cb;
		return;
	}
	if (__check_panel_type (p, PANEL_CMD_DISASMSUMMARY)) {
		p->model->print_cb = __print_disasmsummary_cb;
		return;
	}
	p->model->print_cb = __print_default_cb;
}