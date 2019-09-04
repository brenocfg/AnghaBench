#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* panelsMenu; } ;
struct TYPE_12__ {TYPE_6__* panels; } ;
struct TYPE_11__ {TYPE_1__* view; } ;
struct TYPE_10__ {int depth; int /*<<< orphan*/  n_refresh; TYPE_4__** refreshPanels; TYPE_2__** history; } ;
struct TYPE_9__ {size_t selectedIndex; TYPE_4__* p; int /*<<< orphan*/  name; struct TYPE_9__** sub; } ;
struct TYPE_8__ {int refresh; } ;
typedef  TYPE_2__ RPanelsMenuItem ;
typedef  TYPE_3__ RPanelsMenu ;
typedef  TYPE_4__ RPanel ;
typedef  TYPE_5__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  r_core_cmdf (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_6__*,int) ; 

__attribute__((used)) static int colorsCb(void *user) {
	RCore *core = (RCore *)user;
	RPanelsMenu *menu = core->panels->panelsMenu;
	RPanelsMenuItem *parent = menu->history[menu->depth - 1];
	RPanelsMenuItem *child = parent->sub[parent->selectedIndex];
	r_core_cmdf (core, "eco %s", child->name);
	setRefreshAll (core->panels, false);
	int i;
	for (i = 1; i < menu->depth; i++) {
		RPanel *p = menu->history[i]->p;
		p->view->refresh = true;
		menu->refreshPanels[menu->n_refresh++] = p;
	}
	return 0;
}