#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* panels_menu; } ;
struct TYPE_10__ {TYPE_5__* panels; } ;
struct TYPE_9__ {int depth; } ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_MODE_DEFAULT ; 
 int /*<<< orphan*/  __create_default_panels (TYPE_2__*) ; 
 int /*<<< orphan*/  __init_panels (TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  __panels_layout (TYPE_5__*) ; 
 int /*<<< orphan*/  __set_mode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_2__*,int,int) ; 

int __load_layout_default_cb(void *user) {
	RCore *core = (RCore *)user;
	__init_panels (core, core->panels);
	__create_default_panels (core);
	__panels_layout (core->panels);
	__set_refresh_all (core, false, false);
	core->panels->panels_menu->depth = 1;
	__set_mode (core, PANEL_MODE_DEFAULT);
	return 0;
}