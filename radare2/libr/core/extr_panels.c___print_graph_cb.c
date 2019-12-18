#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* cons; TYPE_2__* panels; } ;
struct TYPE_9__ {scalar_t__ autoUpdate; } ;
struct TYPE_8__ {int /*<<< orphan*/ * event_resize; TYPE_3__* event_data; } ;
typedef  int /*<<< orphan*/  RPanel ;
typedef  TYPE_3__ RCore ;
typedef  int /*<<< orphan*/ * RConsEvent ;

/* Variables and functions */
 scalar_t__ __check_func_diff (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ __do_panels_refreshOneShot ; 
 char* __find_cmd_str_cache (TYPE_3__*,int /*<<< orphan*/ *) ; 
 char* __handle_cmd_str_cache (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __update_panel_contents (TYPE_3__*,int /*<<< orphan*/ *,char*) ; 

void __print_graph_cb(void *user, void *p) {
	RCore *core = (RCore *)user;
	RPanel *panel = (RPanel *)p;
	bool update = core->panels->autoUpdate && __check_func_diff (core, panel);
	char *cmdstr = __find_cmd_str_cache (core, panel);
	if (update || !cmdstr) {
		cmdstr = __handle_cmd_str_cache (core, panel, false);
	}
	core->cons->event_resize = NULL;
	core->cons->event_data = core;
	core->cons->event_resize = (RConsEvent) __do_panels_refreshOneShot;
	__update_panel_contents (core, panel, cmdstr);
}