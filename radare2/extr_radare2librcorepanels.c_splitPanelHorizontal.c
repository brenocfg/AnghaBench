#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_3__* panels; } ;
struct TYPE_16__ {TYPE_2__* view; } ;
struct TYPE_15__ {scalar_t__ curnode; } ;
struct TYPE_13__ {int h; int /*<<< orphan*/  w; scalar_t__ y; int /*<<< orphan*/  x; } ;
struct TYPE_14__ {TYPE_1__ pos; scalar_t__ curpos; } ;
typedef  TYPE_3__ RPanels ;
typedef  TYPE_4__ RPanel ;
typedef  TYPE_5__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  checkPanelNum (TYPE_3__*) ; 
 TYPE_4__* getPanel (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  insertPanel (TYPE_5__*,scalar_t__,char const*,char const*,int) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_3__*,int) ; 

__attribute__((used)) static void splitPanelHorizontal(RCore *core, RPanel *p, const char *name, const char*cmd, bool cache) {
	RPanels *panels = core->panels;
	if (!checkPanelNum (panels)) {
		return;
	}
	insertPanel (core, panels->curnode + 1, name, cmd, cache);
	RPanel *next = getPanel (panels, panels->curnode + 1);
	int oheight = p->view->pos.h;
	p->view->curpos = 0;
	p->view->pos.h = oheight / 2 + 1;
	next->view->pos.x = p->view->pos.x;
	next->view->pos.y = p->view->pos.y + p->view->pos.h - 1;
	next->view->pos.w = p->view->pos.w;
	next->view->pos.h = oheight - p->view->pos.h + 1;
	setRefreshAll (panels, false);
}