#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* panels; } ;
struct TYPE_5__ {int n_panels; int /*<<< orphan*/ ** panel; } ;
typedef  TYPE_1__ RPanels ;
typedef  int /*<<< orphan*/  RPanel ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int PANEL_NUM_LIMIT ; 
 int /*<<< orphan*/  __init_panel_param (TYPE_2__*,int /*<<< orphan*/ *,char const*,char const*) ; 

void __insert_panel(RCore *core, int n, const char *name, const char *cmd) {
	RPanels *panels = core->panels;
	if (panels->n_panels + 1 > PANEL_NUM_LIMIT) {
		return;
	}
	RPanel **panel = panels->panel;
	int i;
	RPanel *last = panel[panels->n_panels];
	for (i = panels->n_panels - 1; i >= n; i--) {
		panel[i + 1] = panel[i];
	}
	panel[n] = last;
	__init_panel_param (core, panel[n], name, cmd);
}