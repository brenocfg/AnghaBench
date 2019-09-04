#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* view; } ;
struct TYPE_11__ {int n_panels; } ;
struct TYPE_9__ {int w; int h; } ;
struct TYPE_10__ {TYPE_1__ pos; } ;
typedef  TYPE_3__ RPanels ;
typedef  TYPE_4__ RPanel ;

/* Variables and functions */
 int /*<<< orphan*/  delPanel (TYPE_3__*,int) ; 
 TYPE_4__* getPanel (TYPE_3__*,int) ; 

__attribute__((used)) static void delInvalidPanels(RPanels *panels) {
	int i;
	for (i = 1; i < panels->n_panels; i++) {
		RPanel *panel = getPanel (panels, i);
		if (panel->view->pos.w < 2) {
			delPanel (panels, i);
			delInvalidPanels (panels);
			break;
		}
		if (panel->view->pos.h < 2) {
			delPanel (panels, i);
			delInvalidPanels (panels);
			break;
		}
	}
}