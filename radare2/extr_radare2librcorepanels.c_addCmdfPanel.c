#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {TYPE_5__* panels; } ;
struct TYPE_24__ {TYPE_2__* view; } ;
struct TYPE_23__ {scalar_t__ curnode; TYPE_4__* panelsMenu; } ;
struct TYPE_22__ {int depth; TYPE_3__** history; } ;
struct TYPE_21__ {size_t selectedIndex; int /*<<< orphan*/  name; struct TYPE_21__** sub; } ;
struct TYPE_19__ {int y; int h; int /*<<< orphan*/  w; scalar_t__ x; } ;
struct TYPE_20__ {TYPE_1__ pos; } ;
typedef  TYPE_3__ RPanelsMenuItem ;
typedef  TYPE_4__ RPanelsMenu ;
typedef  TYPE_5__ RPanels ;
typedef  TYPE_6__ RPanel ;
typedef  TYPE_7__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CONFIG_SIDEPANEL_W ; 
 int /*<<< orphan*/  PANEL_MODE_DEFAULT ; 
 int /*<<< orphan*/  adjustSidePanels (TYPE_7__*) ; 
 int /*<<< orphan*/  checkPanelNum (TYPE_5__*) ; 
 TYPE_6__* getPanel (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insertPanel (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  loadCmdf (TYPE_7__*,TYPE_6__*,char*,char*) ; 
 int /*<<< orphan*/  r_cons_get_size (int*) ; 
 int /*<<< orphan*/  setCmdStrCache (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setMode (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_5__*,int) ; 

__attribute__((used)) static int addCmdfPanel(RCore *core, char *input, char *str) {
	RPanels *panels = core->panels;
	if (!checkPanelNum (panels)) {
		return 0;
	}
	int h;
	(void)r_cons_get_size (&h);
	RPanelsMenu *menu = core->panels->panelsMenu;
	RPanelsMenuItem *parent = menu->history[menu->depth - 1];
	RPanelsMenuItem *child = parent->sub[parent->selectedIndex];
	adjustSidePanels (core);
	insertPanel (core, 0, child->name, "", true);
	RPanel *p0 = getPanel (panels, 0);
	p0->view->pos.x = 0;
	p0->view->pos.y = 1;
	p0->view->pos.w = PANEL_CONFIG_SIDEPANEL_W;
	p0->view->pos.h = h - 1;
	setCmdStrCache (p0, loadCmdf (core, p0, input, str));
	panels->curnode = 0;
	setRefreshAll (panels, false);
	setMode (panels, PANEL_MODE_DEFAULT);
	return 0;
}