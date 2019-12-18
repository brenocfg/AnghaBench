#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int x; int w; int y; int h; } ;
struct TYPE_19__ {TYPE_1__* panels; } ;
struct TYPE_18__ {int depth; TYPE_6__** history; int /*<<< orphan*/  n_refresh; TYPE_5__** refreshPanels; TYPE_2__* root; } ;
struct TYPE_17__ {size_t selectedIndex; TYPE_5__* p; struct TYPE_17__** sub; } ;
struct TYPE_16__ {TYPE_4__* view; TYPE_3__* model; } ;
struct TYPE_15__ {int refresh; TYPE_9__ pos; } ;
struct TYPE_14__ {int /*<<< orphan*/  type; int /*<<< orphan*/  title; } ;
struct TYPE_13__ {int selectedIndex; } ;
struct TYPE_12__ {TYPE_7__* panels_menu; } ;
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  TYPE_6__ RPanelsMenuItem ;
typedef  TYPE_7__ RPanelsMenu ;
typedef  TYPE_8__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_TYPE_MENU ; 
 int /*<<< orphan*/ * __draw_menu (TYPE_8__*,TYPE_6__*) ; 
 int /*<<< orphan*/  __set_pos (TYPE_9__*,int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int r_str_bounds (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  r_strbuf_drain (int /*<<< orphan*/ *) ; 

int __open_menu_cb (void *user) {
	RCore* core = (RCore *)user;
	RPanelsMenu *menu = core->panels->panels_menu;
	RPanelsMenuItem *parent = menu->history[menu->depth - 1];
	RPanelsMenuItem *child = parent->sub[parent->selectedIndex];
	if (menu->depth < 2) {
		__set_pos (&child->p->view->pos, menu->root->selectedIndex * 6, 1);
	} else {
		RPanelsMenuItem *p = menu->history[menu->depth - 2];
		RPanelsMenuItem *parent2 = p->sub[p->selectedIndex];
		__set_pos (&child->p->view->pos, parent2->p->view->pos.x + parent2->p->view->pos.w - 1,
				menu->depth == 2 ? parent2->p->view->pos.y + parent2->selectedIndex : parent2->p->view->pos.y);
	}
	RStrBuf *buf = __draw_menu (core, child);
	if (!buf) {
		return 0;
	}
	free (child->p->model->title);
	child->p->model->title = r_strbuf_drain (buf);
	child->p->view->pos.w = r_str_bounds (child->p->model->title, &child->p->view->pos.h);
	child->p->view->pos.h += 4;
	child->p->model->type = PANEL_TYPE_MENU;
	child->p->view->refresh = true;
	menu->refreshPanels[menu->n_refresh++] = child->p;
	menu->history[menu->depth++] = child;
	return 0;
}