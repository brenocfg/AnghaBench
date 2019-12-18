#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * model; } ;
typedef  int /*<<< orphan*/  RPanels ;
typedef  int /*<<< orphan*/  RPanelModel ;
typedef  TYPE_1__ RPanel ;

/* Variables and functions */
 TYPE_1__* __get_panel (int /*<<< orphan*/ *,int) ; 

void __swap_panels(RPanels *panels, int p0, int p1) {
	RPanel *panel0 = __get_panel (panels, p0);
	RPanel *panel1 = __get_panel (panels, p1);
	RPanelModel *tmp = panel0->model;

	panel0->model = panel1->model;
	panel1->model = tmp;
}