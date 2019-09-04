#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {scalar_t__ h; scalar_t__ w; } ;
struct TYPE_27__ {TYPE_6__* cons; } ;
struct TYPE_26__ {TYPE_3__* view; TYPE_1__* model; } ;
struct TYPE_25__ {TYPE_5__* context; } ;
struct TYPE_23__ {int /*<<< orphan*/  graph_box; int /*<<< orphan*/  graph_box2; } ;
struct TYPE_24__ {TYPE_4__ pal; } ;
struct TYPE_21__ {scalar_t__ y; scalar_t__ x; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct TYPE_22__ {int refresh; TYPE_2__ pos; int /*<<< orphan*/  sy; int /*<<< orphan*/  sx; } ;
struct TYPE_20__ {scalar_t__ type; } ;
typedef  TYPE_7__ RPanel ;
typedef  TYPE_8__ RCore ;
typedef  TYPE_9__ RConsCanvas ;

/* Variables and functions */
 scalar_t__ PANEL_TYPE_MENU ; 
 int R_MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defaultPanelPrint (TYPE_8__*,TYPE_9__*,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  menuPanelPrint (TYPE_9__*,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  r_cons_canvas_box (TYPE_9__*,scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_cons_canvas_fill (TYPE_9__*,scalar_t__,scalar_t__,int,int,char) ; 

__attribute__((used)) static void panelPrint(RCore *core, RConsCanvas *can, RPanel *panel, int color) {
	if (!can || !panel|| !panel->view->refresh) {
		return;
	}

	if (can->w <= panel->view->pos.x || can->h <= panel->view->pos.y) {
		return;
	}
	panel->view->refresh = false;
	int w = R_MIN (can->w - panel->view->pos.x, panel->view->pos.w);
	int h = R_MIN (can->h - panel->view->pos.y, panel->view->pos.h);
	r_cons_canvas_fill (can, panel->view->pos.x, panel->view->pos.y, w, h, ' ');
	if (panel->model->type == PANEL_TYPE_MENU) {
		menuPanelPrint (can, panel, panel->view->sx, panel->view->sy, w, h);
	} else {
		defaultPanelPrint (core, can, panel, panel->view->sx, panel->view->sy, w, h, color);
	}
	if (color) {
		r_cons_canvas_box (can, panel->view->pos.x, panel->view->pos.y, w, h, core->cons->context->pal.graph_box2);
	} else {
		r_cons_canvas_box (can, panel->view->pos.x, panel->view->pos.y, w, h, core->cons->context->pal.graph_box);
	}
}