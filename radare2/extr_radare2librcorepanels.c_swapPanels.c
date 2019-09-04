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
 TYPE_1__* getPanel (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void swapPanels(RPanels *panels, int p0, int p1) {
	RPanel *panel0 = getPanel (panels, p0);
	RPanel *panel1 = getPanel (panels, p1);
	RPanelModel *tmp = panel0->model;

	panel0->model = panel1->model;
	panel1->model = tmp;
}