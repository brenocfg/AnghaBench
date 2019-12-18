#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int x; int w; int y; } ;
struct TYPE_10__ {TYPE_1__* view; } ;
struct TYPE_9__ {int n_panels; int columnWidth; } ;
struct TYPE_8__ {TYPE_4__ pos; } ;
typedef  TYPE_2__ RPanels ;
typedef  TYPE_3__ RPanel ;

/* Variables and functions */
 int R_MAX (int,int /*<<< orphan*/ ) ; 
 TYPE_3__* __get_panel (TYPE_2__*,int) ; 
 int /*<<< orphan*/  __set_geometry (TYPE_4__*,int,int,int,int) ; 
 int r_cons_get_size (int*) ; 

void __layout_default(RPanels *panels) {
	int h, w = r_cons_get_size (&h);
	int ph = (h - 1) / (panels->n_panels - 1);
	int i;
	int colpos = w - panels->columnWidth;
	RPanel *p0 = __get_panel (panels, 0);
	if (panels->n_panels <= 1) {
		__set_geometry (&p0->view->pos, 0, 1, w, h - 1);
		return;
	}
	__set_geometry (&p0->view->pos, 0, 1, colpos + 1, h - 1);

	int pos_x = p0->view->pos.x + p0->view->pos.w - 1;
	for (i = 1; i < panels->n_panels; i++) {
		RPanel *p = __get_panel (panels, i);
		int tmp_w = R_MAX (w - colpos, 0);
		int tmp_h = (i + 1) == panels->n_panels ? h - p->view->pos.y : ph;
		__set_geometry(&p->view->pos, pos_x, 2 + (ph * (i - 1)) - 1, tmp_w, tmp_h + 1);
	}
}