#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* view; } ;
struct TYPE_8__ {int /*<<< orphan*/  panels; } ;
struct TYPE_7__ {int refresh; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_MODE_DEFAULT ; 
 int /*<<< orphan*/  __clear_panels_menu (TYPE_2__*) ; 
 TYPE_5__* __get_cur_panel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_mode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_save_panels_layout (TYPE_2__*) ; 

int __save_layout_cb(void *user) {
	RCore *core = (RCore *)user;
	r_save_panels_layout (core);
	__set_mode (core, PANEL_MODE_DEFAULT);
	__clear_panels_menu (core);
	__get_cur_panel (core->panels)->view->refresh = true;
	return 0;
}