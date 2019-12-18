#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_1__* panels; } ;
struct TYPE_19__ {int /*<<< orphan*/  curnode; int /*<<< orphan*/  fun; } ;
typedef  TYPE_1__ RPanels ;
typedef  int /*<<< orphan*/  RPanel ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  DOWN ; 
 int /*<<< orphan*/  HORIZONTAL ; 
 int /*<<< orphan*/  LEFT ; 
 int /*<<< orphan*/  PANEL_FUN_SAKURA ; 
 int /*<<< orphan*/  PANEL_FUN_SNOW ; 
 int /*<<< orphan*/  RIGHT ; 
 int /*<<< orphan*/  R_STR_ISNOTEMPTY (char*) ; 
 int /*<<< orphan*/  UP ; 
 int /*<<< orphan*/  VERTICAL ; 
 int /*<<< orphan*/  __create_panel_input (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __dismantle_del_panel (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * __get_cur_panel (TYPE_1__*) ; 
 int /*<<< orphan*/  __handle_tab_key (TYPE_2__*,int) ; 
 int /*<<< orphan*/  __move_to_direction (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __replace_cmd (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  __reset_snow (TYPE_1__*) ; 
 int /*<<< orphan*/  __resize_panel_down (TYPE_1__*) ; 
 int /*<<< orphan*/  __resize_panel_left (TYPE_1__*) ; 
 int /*<<< orphan*/  __resize_panel_right (TYPE_1__*) ; 
 int /*<<< orphan*/  __resize_panel_up (TYPE_1__*) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_2__*,int,int) ; 
 char* __show_status_input (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  __toggle_window_mode (TYPE_2__*) ; 
 int /*<<< orphan*/  __toggle_zoom_mode (TYPE_2__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_switchbuf (int) ; 

bool __handle_window_mode(RCore *core, const int key) {
	RPanels *panels = core->panels;
	RPanel *cur = __get_cur_panel (panels);
	r_cons_switchbuf (false);
	switch (key) {
	case 'Q':
	case 'q':
	case 'w':
		__toggle_window_mode (core);
		break;
	case 0x0d:
		__toggle_zoom_mode (core);
		break;
	case 9: // tab
		__handle_tab_key (core, false);
		break;
	case 'Z': // shift-tab
		__handle_tab_key (core, true);
		break;
	case 'e':
	{
		char *cmd = __show_status_input (core, "New command: ");
		if (R_STR_ISNOTEMPTY (cmd)) {
			__replace_cmd (core, cmd, cmd);
		}
		free (cmd);
	}
		break;
	case 'h':
		if (__move_to_direction (core, LEFT)) {
			__set_refresh_all (core, false, false);
		}
		if (panels->fun == PANEL_FUN_SNOW || panels->fun == PANEL_FUN_SAKURA) {
			__reset_snow (panels);
		}
		break;
	case 'j':
		if (__move_to_direction (core, DOWN)) {
			__set_refresh_all (core, false, false);
		}
		if (panels->fun == PANEL_FUN_SNOW || panels->fun == PANEL_FUN_SAKURA) {
			__reset_snow (panels);
		}
		break;
	case 'k':
		if (__move_to_direction (core, UP)) {
			__set_refresh_all (core, false, false);
		}
		if (panels->fun == PANEL_FUN_SNOW || panels->fun == PANEL_FUN_SAKURA) {
			__reset_snow (panels);
		}
		break;
	case 'l':
		if (__move_to_direction (core, RIGHT)) {
			__set_refresh_all (core, false, false);
		}
		if (panels->fun == PANEL_FUN_SNOW || panels->fun == PANEL_FUN_SAKURA) {
			__reset_snow (panels);
		}
		break;
	case 'H':
		r_cons_switchbuf (false);
		__resize_panel_left (panels);
		break;
	case 'L':
		r_cons_switchbuf (false);
		__resize_panel_right (panels);
		break;
	case 'J':
		r_cons_switchbuf (false);
		__resize_panel_down (panels);
		break;
	case 'K':
		r_cons_switchbuf (false);
		__resize_panel_up (panels);
		break;
	case 'n':
		__create_panel_input (core, cur, VERTICAL, NULL);
		break;
	case 'N':
		__create_panel_input (core, cur, HORIZONTAL, NULL);
		break;
	case 'X':
		__dismantle_del_panel (core, cur, panels->curnode);
		__set_refresh_all (core, false, false);
		break;
	case '"':
	case ':':
	case ';':
	case '/':
	case 'd':
	case 'b':
	case 'p':
	case 'P':
	case 't':
	case 'T':
	case '?':
	case '|':
	case '-':
		return false;
	}
	return true;
}