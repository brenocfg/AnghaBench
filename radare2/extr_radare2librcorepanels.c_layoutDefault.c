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
struct TYPE_11__ {TYPE_2__* view; } ;
struct TYPE_10__ {int n_panels; int columnWidth; } ;
struct TYPE_8__ {int x; int y; int w; int h; } ;
struct TYPE_9__ {TYPE_1__ pos; } ;
typedef  TYPE_3__ RPanels ;
typedef  TYPE_4__ RPanel ;

/* Variables and functions */
 TYPE_4__* getPanel (TYPE_3__*,int) ; 
 int r_cons_get_size (int*) ; 

__attribute__((used)) static void layoutDefault(RPanels *panels) {
	int h, w = r_cons_get_size (&h);
	int ph = (h - 1) / (panels->n_panels - 2);
	int i;
	int colpos = w - panels->columnWidth;
	RPanel *p0 = getPanel (panels, 0);
	RPanel *p1 = getPanel (panels, 1);
	p0->view->pos.x = 0;
	p0->view->pos.y = 1;
	if (panels->n_panels <= 1) {
		p0->view->pos.w = w;
		p0->view->pos.h = h - 1;
		return;
	}
	p0->view->pos.w = colpos / 2 + 1;
	p0->view->pos.h = h - 1;
	p1->view->pos.x = colpos / 2;
	p1->view->pos.y = 1;
	p1->view->pos.w = colpos / 2 + 1;
	p1->view->pos.h = h - 1;

	int pos_x = p1->view->pos.x + p1->view->pos.w - 1;
	for (i = 2; i < panels->n_panels; i++) {
		RPanel *p = getPanel (panels, i);
		p->view->pos.x = pos_x;
		p->view->pos.y = 2 + (ph * (i - 2));
		p->view->pos.w = w - colpos;
		if (p->view->pos.w < 0) {
			p->view->pos.w = 0;
		}
		if ((i + 1) == panels->n_panels) {
			p->view->pos.h = h - p->view->pos.y;
		} else {
			p->view->pos.h = ph;
		}
		p->view->pos.y--;
		p->view->pos.h++;
	}
}