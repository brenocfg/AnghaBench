#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* panelsMenu; } ;
struct TYPE_11__ {int depth; int n_refresh; TYPE_3__** history; TYPE_2__** refreshPanels; } ;
struct TYPE_10__ {TYPE_2__* p; } ;
struct TYPE_9__ {TYPE_1__* view; } ;
struct TYPE_8__ {int refresh; } ;
typedef  TYPE_4__ RPanelsMenu ;
typedef  TYPE_5__ RPanels ;

/* Variables and functions */
 int /*<<< orphan*/  setRefreshAll (TYPE_5__*,int) ; 

__attribute__((used)) static void removeMenu(RPanels *panels) {
	RPanelsMenu *menu = panels->panelsMenu;
	int i;
	menu->depth--;
	for (i = 1; i < menu->depth; i++) {
		menu->history[i]->p->view->refresh = true;
		menu->refreshPanels[i - 1] = menu->history[i]->p;
	}
	menu->n_refresh = menu->depth - 1;
	setRefreshAll (panels, false);
}