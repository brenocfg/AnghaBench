#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* panels; } ;
struct TYPE_6__ {int n_panels; int /*<<< orphan*/  curnode; int /*<<< orphan*/ ** panel; } ;
typedef  TYPE_1__ RPanels ;
typedef  int /*<<< orphan*/  RPanel ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/ * __get_panel (TYPE_1__*,int) ; 
 int /*<<< orphan*/  __set_curnode (TYPE_2__*,int /*<<< orphan*/ ) ; 

void __del_panel(RCore *core, int pi) {
	int i;
	RPanels *panels = core->panels;
	RPanel *tmp = __get_panel (panels, pi);
	if (!tmp) {
		return;
	}
	for (i = pi; i < (panels->n_panels - 1); i++) {
		panels->panel[i] = panels->panel[i + 1];
	}
	panels->panel[panels->n_panels - 1] = tmp;
	panels->n_panels--;
	__set_curnode (core, panels->curnode);
}