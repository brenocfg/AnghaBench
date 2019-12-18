#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* panels; } ;
struct TYPE_9__ {scalar_t__ mode; scalar_t__ prevMode; scalar_t__ fun; } ;
typedef  TYPE_1__ RPanels ;
typedef  int /*<<< orphan*/  RPanel ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 scalar_t__ PANEL_FUN_SAKURA ; 
 scalar_t__ PANEL_FUN_SNOW ; 
 scalar_t__ PANEL_MODE_DEFAULT ; 
 scalar_t__ PANEL_MODE_ZOOM ; 
 int /*<<< orphan*/ * __get_cur_panel (TYPE_1__*) ; 
 int /*<<< orphan*/  __maximize_panel_size (TYPE_1__*) ; 
 int /*<<< orphan*/  __reset_snow (TYPE_1__*) ; 
 int /*<<< orphan*/  __restore_panel_pos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __save_panel_pos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_mode (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_2__*,int,int) ; 

void __toggle_zoom_mode(RCore *core) {
	RPanels *panels = core->panels;
	RPanel *cur = __get_cur_panel (panels);
	if (panels->mode != PANEL_MODE_ZOOM) {
		panels->prevMode = panels->mode;
		__set_mode (core, PANEL_MODE_ZOOM);
		__save_panel_pos (cur);
		__maximize_panel_size (panels);
	} else {
		__set_mode (core, panels->prevMode);
		panels->prevMode = PANEL_MODE_DEFAULT;
		__restore_panel_pos (cur);
		__set_refresh_all (core, false, false);
		if (panels->fun == PANEL_FUN_SNOW || panels->fun == PANEL_FUN_SAKURA) {
			__reset_snow (panels);
		}
	}
}