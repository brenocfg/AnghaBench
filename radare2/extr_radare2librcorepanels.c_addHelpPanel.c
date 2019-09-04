#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_3__* panels; } ;
struct TYPE_15__ {TYPE_2__* view; } ;
struct TYPE_14__ {scalar_t__ curnode; } ;
struct TYPE_12__ {int y; int h; int /*<<< orphan*/  w; scalar_t__ x; } ;
struct TYPE_13__ {TYPE_1__ pos; } ;
typedef  TYPE_3__ RPanels ;
typedef  TYPE_4__ RPanel ;
typedef  TYPE_5__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CONFIG_SIDEPANEL_W ; 
 int /*<<< orphan*/  adjustSidePanels (TYPE_5__*) ; 
 TYPE_4__* getPanel (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insertPanel (TYPE_5__*,int /*<<< orphan*/ ,char const*,char const*,int) ; 
 int /*<<< orphan*/  r_cons_get_size (int*) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_3__*,int) ; 

__attribute__((used)) static void addHelpPanel(RCore *core) {
	//TODO: all these things done below are very hacky and refactoring needed
	RPanels *ps = core->panels;
	int h;
	const char *help = "Help";
	(void)r_cons_get_size (&h);
	adjustSidePanels (core);
	insertPanel (core, 0, help, help, true);
	RPanel *p0 = getPanel (ps, 0);
	p0->view->pos.x = 0;
	p0->view->pos.y = 1;
	p0->view->pos.w = PANEL_CONFIG_SIDEPANEL_W;
	p0->view->pos.h = h - 1;
	ps->curnode = 0;
	setRefreshAll (ps, false);
}