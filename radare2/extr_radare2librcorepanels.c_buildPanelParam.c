#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_18__ {int /*<<< orphan*/  n_panels; } ;
struct TYPE_17__ {TYPE_6__* panels; int /*<<< orphan*/  config; TYPE_1__* anal; scalar_t__ offset; } ;
struct TYPE_16__ {TYPE_2__* view; TYPE_3__* model; } ;
struct TYPE_15__ {int cache; scalar_t__ addr; scalar_t__ baseAddr; void* cmd; void* title; int /*<<< orphan*/ * funcName; int /*<<< orphan*/ * rotateCb; scalar_t__ rotate; int /*<<< orphan*/  type; } ;
struct TYPE_14__ {int refresh; scalar_t__ curpos; } ;
struct TYPE_13__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_2__ RPanelView ;
typedef  TYPE_3__ RPanelModel ;
typedef  TYPE_4__ RPanel ;
typedef  TYPE_5__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_STACK ; 
 int /*<<< orphan*/  PANEL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  R_REG_NAME_SP ; 
 scalar_t__ R_STR_ISNOTEMPTY (void*) ; 
 scalar_t__ const r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 char* r_reg_get_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ r_reg_getv (int /*<<< orphan*/ ,char const*) ; 
 void* r_str_dup (void*,char const*) ; 
 int /*<<< orphan*/  setCmdStrCache (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setReadOnly (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setdcb (TYPE_4__*) ; 
 int /*<<< orphan*/  setrcb (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void buildPanelParam(RCore *core, RPanel *p, const char *title, const char *cmd, bool cache) {
	RPanelModel *m = p->model;
	RPanelView *v = p->view;
	m->cache = cache;
	m->type = PANEL_TYPE_DEFAULT;
	m->rotate = 0;
	v->curpos = 0;
	m->addr = core->offset;
	m->rotateCb = NULL;
	setCmdStrCache (p, NULL);
	setReadOnly(p, NULL);
	m->funcName = NULL;
	v->refresh = true;
	if (title) {
		m->title = r_str_dup (m->title, title);
		if (cmd) {
			m->cmd = r_str_dup (m->cmd, cmd);
		} else {
			m->cmd = r_str_dup (m->cmd, "");
		}
	} else if (cmd) {
		m->title = r_str_dup (m->title, cmd);
		m->cmd = r_str_dup (m->cmd, cmd);
	} else {
		m->title = r_str_dup (m->title, "");
		m->cmd = r_str_dup (m->cmd, "");
	}
	if (R_STR_ISNOTEMPTY (m->cmd)) {
		setdcb (p);
		setrcb (core->panels, p);
		if (!strncmp (m->cmd, PANEL_CMD_STACK, strlen (PANEL_CMD_STACK))) {
			const char *sp = r_reg_get_name (core->anal->reg, R_REG_NAME_SP);
			const ut64 stackbase = r_reg_getv (core->anal->reg, sp);
			m->baseAddr = stackbase;
			m->addr = stackbase - r_config_get_i (core->config, "stack.delta");
		}
	}
	core->panels->n_panels++;
	return;
}