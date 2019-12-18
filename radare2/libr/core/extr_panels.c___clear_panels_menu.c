#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ selectedIndex; } ;
struct TYPE_8__ {TYPE_2__* panels; } ;
struct TYPE_7__ {TYPE_1__* panels_menu; } ;
struct TYPE_6__ {int depth; scalar_t__ n_refresh; TYPE_4__* root; TYPE_4__** history; } ;
typedef  TYPE_1__ RPanelsMenu ;
typedef  TYPE_2__ RPanels ;
typedef  TYPE_3__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_panels_menuRec (TYPE_4__*) ; 

void __clear_panels_menu(RCore *core) {
	RPanels *p = core->panels;
	RPanelsMenu *pm = p->panels_menu;
	__clear_panels_menuRec (pm->root);
	pm->root->selectedIndex = 0;
	pm->history[0] = pm->root;
	pm->depth = 1;
	pm->n_refresh = 0;
}