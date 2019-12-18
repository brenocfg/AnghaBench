#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_1__* panels; } ;
struct TYPE_14__ {TYPE_2__* view; } ;
struct TYPE_13__ {int depth; int /*<<< orphan*/  n_refresh; TYPE_5__** refreshPanels; TYPE_3__** history; } ;
struct TYPE_12__ {size_t selectedIndex; TYPE_5__* p; int /*<<< orphan*/  name; struct TYPE_12__** sub; } ;
struct TYPE_11__ {int refresh; } ;
struct TYPE_10__ {TYPE_4__* panels_menu; } ;
typedef  TYPE_3__ RPanelsMenuItem ;
typedef  TYPE_4__ RPanelsMenu ;
typedef  TYPE_5__ RPanel ;
typedef  TYPE_6__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __init_menu_color_settings_layout ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_6__*,int,int) ; 
 int /*<<< orphan*/  __update_menu (TYPE_6__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_core_cmdf (TYPE_6__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_ansi_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int __settings_colors_cb(void *user) {
	RCore *core = (RCore *)user;
	RPanelsMenu *menu = core->panels->panels_menu;
	RPanelsMenuItem *parent = menu->history[menu->depth - 1];
	RPanelsMenuItem *child = parent->sub[parent->selectedIndex];
	r_str_ansi_filter (child->name, NULL, NULL, -1);
	r_core_cmdf (core, "eco %s", child->name);
	__set_refresh_all (core, false, false);
	int i;
	for (i = 1; i < menu->depth; i++) {
		RPanel *p = menu->history[i]->p;
		p->view->refresh = true;
		menu->refreshPanels[menu->n_refresh++] = p;
	}
	__update_menu(core, "Settings.Colors", __init_menu_color_settings_layout);
	return 0;
}