#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* view; } ;
struct TYPE_8__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_6__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_7__ {TYPE_3__ prevPos; TYPE_1__ pos; } ;
typedef  TYPE_4__ RPanel ;

/* Variables and functions */

__attribute__((used)) static void restorePanelPos(RPanel* panel) {
	panel->view->pos.x = panel->view->prevPos.x;
	panel->view->pos.y = panel->view->prevPos.y;
	panel->view->pos.w = panel->view->prevPos.w;
	panel->view->pos.h = panel->view->prevPos.h;
}