#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* view; } ;
struct TYPE_8__ {int n_panels; } ;
struct TYPE_7__ {int /*<<< orphan*/  pos; } ;
typedef  TYPE_2__ RPanels ;
typedef  TYPE_3__ RPanel ;

/* Variables and functions */
 TYPE_3__* __get_panel (TYPE_2__*,int) ; 
 int /*<<< orphan*/  __set_geometry (int /*<<< orphan*/ *,int,int,int,int) ; 
 int r_cons_get_size (int*) ; 

void __layout_equal_hor(RPanels *panels) {
	int h, w = r_cons_get_size (&h);
	int pw = w / panels->n_panels;
	int i, cw = 0;
	for (i = 0; i < panels->n_panels; i++) {
		RPanel *p = __get_panel (panels, i);
		__set_geometry(&p->view->pos, cw, 1, pw, h - 2);
		cw += pw - 1;
		if (i == panels->n_panels - 2) {
			pw = w - cw;
		}
	}
}