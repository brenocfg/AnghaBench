#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_25__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_34__ {TYPE_6__* panels; } ;
struct TYPE_33__ {TYPE_5__* panelsMenu; } ;
struct TYPE_32__ {int depth; TYPE_4__** history; TYPE_2__* root; } ;
struct TYPE_31__ {size_t selectedIndex; int /*<<< orphan*/  (* cb ) (TYPE_7__*) ;struct TYPE_31__** sub; int /*<<< orphan*/  n_sub; } ;
struct TYPE_30__ {int refresh; } ;
struct TYPE_29__ {size_t selectedIndex; size_t n_sub; TYPE_1__** sub; } ;
struct TYPE_28__ {TYPE_3__* view; } ;
struct TYPE_27__ {int /*<<< orphan*/  (* cb ) (TYPE_7__*) ;} ;
typedef  TYPE_4__ RPanelsMenuItem ;
typedef  TYPE_5__ RPanelsMenu ;
typedef  TYPE_6__ RPanels ;
typedef  TYPE_7__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_MODE_DEFAULT ; 
 size_t R_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_25__* getCurPanel (TYPE_6__*) ; 
 int /*<<< orphan*/  handlePrompt (TYPE_7__*,TYPE_6__*) ; 
 int /*<<< orphan*/  handleTabKey (TYPE_7__*,int) ; 
 int /*<<< orphan*/  moveMenuCursor (TYPE_7__*,TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  r_cons_switchbuf (int) ; 
 int /*<<< orphan*/  r_core_cmd0 (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  removeMenu (TYPE_6__*) ; 
 int /*<<< orphan*/  setMode (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setRefreshAll (TYPE_6__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub5 (TYPE_7__*) ; 
 int /*<<< orphan*/  toggleHelp (TYPE_7__*) ; 

__attribute__((used)) static bool handleMenu(RCore *core, const int key) {
	RPanels *panels = core->panels;
	RPanelsMenu *menu = panels->panelsMenu;
	r_cons_switchbuf (false);
	switch (key) {
	case 'h':
		if (menu->depth <= 2) {
			if (menu->root->selectedIndex > 0) {
				menu->root->selectedIndex--;
			} else {
				menu->root->selectedIndex = menu->root->n_sub - 1;
			}
			if (menu->depth == 2) {
				menu->depth = 1;
				setRefreshAll (panels, false);
				menu->root->sub[menu->root->selectedIndex]->cb (core);
			}
		} else {
			removeMenu (panels);
		}
		break;
	case 'j':
		{
			if (menu->depth == 1) {
				RPanelsMenuItem *parent = menu->history[menu->depth - 1];
				parent->sub[parent->selectedIndex]->cb(core);
			} else {
				RPanelsMenuItem *parent = menu->history[menu->depth - 1];
				parent->selectedIndex = R_MIN (parent->n_sub - 1, parent->selectedIndex + 1);
				moveMenuCursor (core, menu, parent);
			}
		}
		break;
	case 'k':
		{
			if (menu->depth < 2) {
				break;
			}
			RPanelsMenuItem *parent = menu->history[menu->depth - 1];
			if (parent->selectedIndex > 0) {
				parent->selectedIndex--;
				moveMenuCursor (core, menu, parent);
			} else if (menu->depth == 2) {
				menu->depth--;
				setRefreshAll (panels, false);
			}
		}
		break;
	case 'l':
		{
			if (menu->depth == 1) {
				menu->root->selectedIndex++;
				menu->root->selectedIndex %= menu->root->n_sub;
				break;
			}
			RPanelsMenuItem *child = menu->history[menu->depth - 1];
			if (child->sub[child->selectedIndex]->sub) {
				child->sub[child->selectedIndex]->cb (core);
			} else {
				menu->root->selectedIndex++;
				menu->root->selectedIndex %= menu->root->n_sub;
				menu->depth = 1;
				setRefreshAll (panels, false);
				menu->root->sub[menu->root->selectedIndex]->cb (core);
			}
		}
		break;
	case 'm':
	case 'q':
	case 'Q':
	case -1:
		if (panels->panelsMenu->depth > 1) {
			removeMenu (panels);
		} else {
			setMode (panels, PANEL_MODE_DEFAULT);
			getCurPanel (panels)->view->refresh = true;
		}
		break;
	case '$':
		r_core_cmd0 (core, "dr PC=$$");
		break;
	case ' ':
	case '\r':
	case '\n':
		{
			RPanelsMenuItem *parent = menu->history[menu->depth - 1];
			RPanelsMenuItem *child = parent->sub[parent->selectedIndex];
			if (child->cb (core)) {
				return false;
			}
		}
		break;
	case 9:
		handleTabKey (core, false);
		break;
	case 'Z':
		handleTabKey (core, true);
		break;
	case ':':
		handlePrompt (core, panels);
		break;
	case '?':
		toggleHelp (core);
		break;
	}
	return true;
}