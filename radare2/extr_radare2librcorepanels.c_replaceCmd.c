#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int cache; int /*<<< orphan*/  type; int /*<<< orphan*/  addr; void* cmd; void* title; } ;
struct TYPE_11__ {int /*<<< orphan*/  offset; int /*<<< orphan*/ * panels; } ;
struct TYPE_10__ {TYPE_9__* model; } ;
typedef  int /*<<< orphan*/  RPanels ;
typedef  TYPE_1__ RPanel ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  RPanelModel ; 
 TYPE_9__* R_NEW0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freePanelModel (TYPE_1__*) ; 
 TYPE_1__* getCurPanel (int /*<<< orphan*/ *) ; 
 void* r_str_dup (void*,char const*) ; 
 int /*<<< orphan*/  setCmdStrCache (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setRefreshAll (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setdcb (TYPE_1__*) ; 
 int /*<<< orphan*/  setrcb (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void replaceCmd(RCore *core, const char *title, const char *cmd, const bool cache) {
	RPanels *panels = core->panels;
	RPanel *cur = getCurPanel (panels);
	freePanelModel (cur);
	cur->model = R_NEW0 (RPanelModel);
	cur->model->title = r_str_dup (cur->model->title, title);
	cur->model->cmd = r_str_dup (cur->model->cmd, cmd);
	cur->model->cache = cache;
	setCmdStrCache (cur, NULL);
	cur->model->addr = core->offset;
	cur->model->type = PANEL_TYPE_DEFAULT;
	setdcb (cur);
	setrcb (panels, cur);
	setRefreshAll (panels, false);
}