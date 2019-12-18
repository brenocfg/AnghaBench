#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {TYPE_4__* panels; } ;
struct TYPE_24__ {TYPE_1__* view; } ;
struct TYPE_23__ {TYPE_3__* panels_menu; } ;
struct TYPE_22__ {int depth; TYPE_2__** history; } ;
struct TYPE_21__ {size_t selectedIndex; int /*<<< orphan*/  name; struct TYPE_21__** sub; } ;
struct TYPE_20__ {int /*<<< orphan*/  pos; } ;
typedef  TYPE_2__ RPanelsMenuItem ;
typedef  TYPE_3__ RPanelsMenu ;
typedef  TYPE_4__ RPanels ;
typedef  TYPE_5__ RPanel ;
typedef  TYPE_6__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CONFIG_SIDEPANEL_W ; 
 int /*<<< orphan*/  PANEL_MODE_DEFAULT ; 
 int /*<<< orphan*/  __adjust_side_panels (TYPE_6__*) ; 
 int /*<<< orphan*/  __check_panel_num (TYPE_6__*) ; 
 TYPE_5__* __get_panel (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __insert_panel (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  __load_cmdf (TYPE_6__*,TYPE_5__*,char*,char*) ; 
 int /*<<< orphan*/  __set_cmd_str_cache (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_curnode (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_geometry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __set_mode (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  r_cons_get_size (int*) ; 

int __add_cmdf_panel(RCore *core, char *input, char *str) {
	RPanels *panels = core->panels;
	if (!__check_panel_num (core)) {
		return 0;
	}
	int h;
	(void)r_cons_get_size (&h);
	RPanelsMenu *menu = core->panels->panels_menu;
	RPanelsMenuItem *parent = menu->history[menu->depth - 1];
	RPanelsMenuItem *child = parent->sub[parent->selectedIndex];
	__adjust_side_panels (core);
	__insert_panel (core, 0, child->name, "");
	RPanel *p0 = __get_panel (panels, 0);
	__set_geometry (&p0->view->pos, 0, 1, PANEL_CONFIG_SIDEPANEL_W, h - 1);
	__set_cmd_str_cache (core, p0, __load_cmdf (core, p0, input, str));
	__set_curnode (core, 0);
	__set_refresh_all (core, false, false);
	__set_mode (core, PANEL_MODE_DEFAULT);
	return 0;
}