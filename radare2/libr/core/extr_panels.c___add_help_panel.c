#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * panels; } ;
struct TYPE_11__ {TYPE_1__* view; } ;
struct TYPE_10__ {int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  RPanels ;
typedef  TYPE_2__ RPanel ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CONFIG_SIDEPANEL_W ; 
 int /*<<< orphan*/  __adjust_side_panels (TYPE_3__*) ; 
 TYPE_2__* __get_panel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __insert_panel (TYPE_3__*,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  __set_curnode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_geometry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  r_cons_get_size (int*) ; 

void __add_help_panel(RCore *core) {
	//TODO: all these things done below are very hacky and refactoring needed
	RPanels *ps = core->panels;
	int h;
	const char *help = "Help";
	(void)r_cons_get_size (&h);
	__adjust_side_panels (core);
	__insert_panel (core, 0, help, help);
	RPanel *p0 = __get_panel (ps, 0);
	__set_geometry (&p0->view->pos, 0, 1, PANEL_CONFIG_SIDEPANEL_W, h - 1);
	__set_curnode (core, 0);
	__set_refresh_all (core, false, false);
}