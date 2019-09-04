#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* view; } ;
struct TYPE_12__ {TYPE_1__* can; } ;
struct TYPE_11__ {int y; scalar_t__ h; int /*<<< orphan*/  w; scalar_t__ x; } ;
struct TYPE_10__ {int refresh; TYPE_3__ pos; } ;
struct TYPE_9__ {scalar_t__ h; int /*<<< orphan*/  w; } ;
typedef  TYPE_4__ RPanels ;
typedef  TYPE_5__ RPanel ;

/* Variables and functions */
 TYPE_5__* getCurPanel (TYPE_4__*) ; 

__attribute__((used)) static void maximizePanelSize(RPanels *panels) {
	RPanel *cur = getCurPanel (panels);
	cur->view->pos.x = 0;
	cur->view->pos.y = 1;
	cur->view->pos.w = panels->can->w;
	cur->view->pos.h = panels->can->h - 1;
	cur->view->refresh = true;
}