#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* view; TYPE_2__* model; } ;
struct TYPE_14__ {int /*<<< orphan*/  n_refresh; TYPE_6__** refreshPanels; } ;
struct TYPE_13__ {TYPE_6__* p; } ;
struct TYPE_10__ {int h; int /*<<< orphan*/  w; } ;
struct TYPE_12__ {int refresh; TYPE_1__ pos; } ;
struct TYPE_11__ {int /*<<< orphan*/  type; int /*<<< orphan*/  title; } ;
typedef  int /*<<< orphan*/  RStrBuf ;
typedef  TYPE_4__ RPanelsMenuItem ;
typedef  TYPE_5__ RPanelsMenu ;
typedef  TYPE_6__ RPanel ;
typedef  int /*<<< orphan*/  RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_TYPE_MENU ; 
 int /*<<< orphan*/ * drawMenu (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  r_str_bounds (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  r_strbuf_drain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void moveMenuCursor(RCore *core, RPanelsMenu *menu, RPanelsMenuItem *parent) {
	RPanel *p = parent->p;
	RStrBuf *buf = drawMenu (core, parent);
	if (!buf) {
		return;
	}
	p->model->title = r_strbuf_drain (buf);
	p->view->pos.w = r_str_bounds (p->model->title, &p->view->pos.h);
	p->view->pos.h += 4;
	p->model->type = PANEL_TYPE_MENU;
	p->view->refresh = true;
	menu->refreshPanels[menu->n_refresh++] = p;
}