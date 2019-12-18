#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* panels_menu; } ;
struct TYPE_11__ {TYPE_7__* panels; } ;
struct TYPE_10__ {int depth; TYPE_1__** history; } ;
struct TYPE_9__ {size_t selectedIndex; int /*<<< orphan*/  name; struct TYPE_9__** sub; } ;
typedef  TYPE_1__ RPanelsMenuItem ;
typedef  TYPE_2__ RPanelsMenu ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_MODE_DEFAULT ; 
 int /*<<< orphan*/  __create_default_panels (TYPE_3__*) ; 
 int /*<<< orphan*/  __panels_layout (TYPE_7__*) ; 
 int /*<<< orphan*/  __set_curnode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_mode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_load_panels_layout (TYPE_3__*,int /*<<< orphan*/ ) ; 

int __load_layout_saved_cb(void *user) {
	RCore *core = (RCore *)user;
	RPanelsMenu *menu = core->panels->panels_menu;
	RPanelsMenuItem *parent = menu->history[menu->depth - 1];
	RPanelsMenuItem *child = parent->sub[parent->selectedIndex];
	if (!r_load_panels_layout (core, child->name)) {
		__create_default_panels (core);
		__panels_layout (core->panels);
	}
	__set_curnode (core, 0);
	core->panels->panels_menu->depth = 1;
	__set_mode (core, PANEL_MODE_DEFAULT);
	return 0;
}