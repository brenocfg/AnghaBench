#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * model; } ;
struct TYPE_7__ {int n_panels; } ;
typedef  TYPE_1__ RPanels ;
typedef  int /*<<< orphan*/  RPanelModel ;
typedef  TYPE_2__ RPanel ;

/* Variables and functions */
 TYPE_2__* getPanel (TYPE_1__*,int) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_1__*,int) ; 

__attribute__((used)) static void rotatePanels(RPanels *panels, bool rev) {
	RPanel *first = getPanel (panels, 0);
	RPanel *last = getPanel (panels, panels->n_panels - 1);
	int i;
	RPanelModel *tmp_model;
	if (!rev) {
		tmp_model = first->model;
		for (i = 0; i < panels->n_panels - 1; i++) {
			RPanel *p0 = getPanel (panels, i);
			RPanel *p1 = getPanel (panels, i + 1);
			p0->model = p1->model;
		}
		last->model = tmp_model;
	} else {
		tmp_model = last->model;
		for (i = panels->n_panels - 1; i > 0; i--) {
			RPanel *p0 = getPanel (panels, i);
			RPanel *p1 = getPanel (panels, i - 1);
			p0->model = p1->model;
		}
		first->model = tmp_model;
	}
	setRefreshAll (panels, false);
}