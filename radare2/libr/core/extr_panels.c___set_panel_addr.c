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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_13__ {TYPE_2__* panels; } ;
struct TYPE_12__ {TYPE_3__* view; TYPE_1__* model; } ;
struct TYPE_11__ {int refresh; } ;
struct TYPE_10__ {scalar_t__ autoUpdate; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
typedef  TYPE_4__ RPanel ;
typedef  TYPE_5__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __set_refresh_all (TYPE_5__*,int,int) ; 

void __set_panel_addr(RCore *core, RPanel *panel, ut64 addr) {
	panel->model->addr = addr;
	// TODO: implement sync() __seek_all (core, addr);
	if (core->panels->autoUpdate) {
		__set_refresh_all (core, false, false);
		return;
	}
	panel->view->refresh = true;
}