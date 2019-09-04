#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* model; } ;
struct TYPE_4__ {void* directionCb; int /*<<< orphan*/  cmd; scalar_t__ readOnly; scalar_t__ cmdStrCache; } ;
typedef  TYPE_2__ RPanel ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 int /*<<< orphan*/  PANEL_CMD_GRAPH ; 
 int /*<<< orphan*/  PANEL_CMD_HEXDUMP ; 
 int /*<<< orphan*/  PANEL_CMD_REGISTERS ; 
 int /*<<< orphan*/  PANEL_CMD_STACK ; 
 void* directionDefaultCb ; 
 void* directionDisassemblyCb ; 
 void* directionGraphCb ; 
 void* directionHexdumpCb ; 
 void* directionRegisterCb ; 
 void* directionStackCb ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setdcb(RPanel *p) {
	if (!p->model->cmd) {
		return;
	}
	if (p->model->cmdStrCache || p->model->readOnly) {
		p->model->directionCb = directionDefaultCb;
		return;
	}
	if (!strncmp (p->model->cmd, PANEL_CMD_STACK, strlen (PANEL_CMD_STACK))) {
		p->model->directionCb = directionStackCb;
	} else if (!strncmp (p->model->cmd, PANEL_CMD_GRAPH, strlen (PANEL_CMD_GRAPH))) {
		p->model->directionCb = directionGraphCb;
	} else if (!strncmp (p->model->cmd, PANEL_CMD_DISASSEMBLY, strlen (PANEL_CMD_DISASSEMBLY)) &&
			strcmp (p->model->cmd, "pdc")) {
		p->model->directionCb = directionDisassemblyCb;
	} else if (!strncmp (p->model->cmd, PANEL_CMD_REGISTERS, strlen (PANEL_CMD_REGISTERS))) {
		p->model->directionCb = directionRegisterCb;
	} else if (!strncmp (p->model->cmd, PANEL_CMD_HEXDUMP, strlen (PANEL_CMD_HEXDUMP))) {
		p->model->directionCb = directionHexdumpCb;
	} else {
		p->model->directionCb = directionDefaultCb;
	}
}