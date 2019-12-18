#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_17__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  offset; int /*<<< orphan*/ * panels; } ;
struct TYPE_19__ {TYPE_17__* model; } ;
struct TYPE_18__ {int /*<<< orphan*/  type; void* cmd; void* title; } ;
typedef  int /*<<< orphan*/  RPanels ;
typedef  TYPE_1__ RPanel ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  RPanelModel ; 
 TYPE_17__* R_NEW0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cache_white_list (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  __free_panel_model (TYPE_1__*) ; 
 TYPE_1__* __get_cur_panel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_cmd_str_cache (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_dcb (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  __set_panel_addr (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_pcb (TYPE_1__*) ; 
 int /*<<< orphan*/  __set_rcb (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_2__*,int,int) ; 
 void* r_str_dup (void*,char const*) ; 

void __replace_cmd(RCore *core, const char *title, const char *cmd) {
	RPanels *panels = core->panels;
	RPanel *cur = __get_cur_panel (panels);
	__free_panel_model (cur);
	cur->model = R_NEW0 (RPanelModel);
	cur->model->title = r_str_dup (cur->model->title, title);
	cur->model->cmd = r_str_dup (cur->model->cmd, cmd);
	__set_cmd_str_cache (core, cur, NULL);
	__set_panel_addr (core, cur, core->offset);
	cur->model->type = PANEL_TYPE_DEFAULT;
	__set_dcb (core, cur);
	__set_pcb (cur);
	__set_rcb (panels, cur);
	__cache_white_list (core, cur);
	__set_refresh_all (core, false, true);
}