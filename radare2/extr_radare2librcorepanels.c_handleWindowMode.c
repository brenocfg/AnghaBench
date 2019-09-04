#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_1__* panels; } ;
struct TYPE_17__ {int /*<<< orphan*/  curnode; int /*<<< orphan*/  fun; } ;
typedef  TYPE_1__ RPanels ;
typedef  int /*<<< orphan*/  RPanel ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  DOWN ; 
 int /*<<< orphan*/  LEFT ; 
 int /*<<< orphan*/  PANEL_FUN_SAKURA ; 
 int /*<<< orphan*/  PANEL_FUN_SNOW ; 
 int /*<<< orphan*/  RIGHT ; 
 int /*<<< orphan*/  UP ; 
 int /*<<< orphan*/  createNewPanel (TYPE_2__*,int) ; 
 int /*<<< orphan*/  dismantleDelPanel (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * getCurPanel (TYPE_1__*) ; 
 int /*<<< orphan*/  handleTabKey (TYPE_2__*,int) ; 
 int /*<<< orphan*/  moveToDirection (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_cons_switchbuf (int) ; 
 int /*<<< orphan*/  resetSnow (TYPE_1__*) ; 
 int /*<<< orphan*/  resizePanelDown (TYPE_1__*) ; 
 int /*<<< orphan*/  resizePanelLeft (TYPE_1__*) ; 
 int /*<<< orphan*/  resizePanelRight (TYPE_1__*) ; 
 int /*<<< orphan*/  resizePanelUp (TYPE_1__*) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_1__*,int) ; 
 int /*<<< orphan*/  toggleWindowMode (TYPE_1__*) ; 
 int /*<<< orphan*/  toggleZoomMode (TYPE_1__*) ; 

__attribute__((used)) static bool handleWindowMode(RCore *core, const int key) {
	RPanels *panels = core->panels;
	RPanel *cur = getCurPanel (panels);
	r_cons_switchbuf (false);
	switch (key) {
	case 'Q':
	case 'q':
	case 'w':
		toggleWindowMode (panels);
		break;
	case 0x0d:
		toggleZoomMode (panels);
		break;
	case 9: // tab
		handleTabKey (core, false);
		break;
	case 'Z': // shift-tab
		handleTabKey (core, true);
		break;
	case 'h':
		if (moveToDirection (panels, LEFT)) {
			setRefreshAll (panels, false);
		}
		if (panels->fun == PANEL_FUN_SNOW || panels->fun == PANEL_FUN_SAKURA) {
			resetSnow (panels);
		}
		break;
	case 'j':
		if (moveToDirection (panels, DOWN)) {
			setRefreshAll (panels, false);
		}
		if (panels->fun == PANEL_FUN_SNOW || panels->fun == PANEL_FUN_SAKURA) {
			resetSnow (panels);
		}
		break;
	case 'k':
		if (moveToDirection (panels, UP)) {
			setRefreshAll (panels, false);
		}
		if (panels->fun == PANEL_FUN_SNOW || panels->fun == PANEL_FUN_SAKURA) {
			resetSnow (panels);
		}
		break;
	case 'l':
		if (moveToDirection (panels, RIGHT)) {
			setRefreshAll (panels, false);
		}
		if (panels->fun == PANEL_FUN_SNOW || panels->fun == PANEL_FUN_SAKURA) {
			resetSnow (panels);
		}
		break;
	case 'H':
		r_cons_switchbuf (false);
		resizePanelLeft (panels);
		break;
	case 'L':
		r_cons_switchbuf (false);
		resizePanelRight (panels);
		break;
	case 'J':
		r_cons_switchbuf (false);
		resizePanelDown (panels);
		break;
	case 'K':
		r_cons_switchbuf (false);
		resizePanelUp (panels);
		break;
	case 'n':
		createNewPanel (core, true);
		break;
	case 'N':
		createNewPanel (core, false);
		break;
	case 'X':
		dismantleDelPanel (panels, cur, panels->curnode);
		setRefreshAll (panels, false);
		break;
	case ':':
	case ';':
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