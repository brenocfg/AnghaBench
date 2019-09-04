#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* print; int /*<<< orphan*/  panels; } ;
struct TYPE_9__ {TYPE_1__* view; } ;
struct TYPE_8__ {int cur_enabled; int col; int /*<<< orphan*/  cur; } ;
struct TYPE_7__ {int /*<<< orphan*/  curpos; } ;
typedef  TYPE_2__ RPrint ;
typedef  TYPE_3__ RPanel ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 TYPE_3__* getCurPanel (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setCursor(RCore *core, bool cur) {
	RPanel *p = getCurPanel (core->panels);
	RPrint *print = core->print;
	print->cur_enabled = cur;
	if (cur) {
		print->cur = p->view->curpos;
	} else {
		p->view->curpos = print->cur;
	}
	print->col = print->cur_enabled ? 1: 0;
}