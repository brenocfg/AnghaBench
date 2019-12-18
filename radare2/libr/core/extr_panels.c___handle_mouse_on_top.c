#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_3__* panels; } ;
struct TYPE_16__ {TYPE_2__* panels_menu; } ;
struct TYPE_15__ {int depth; TYPE_1__** history; } ;
struct TYPE_14__ {int selectedIndex; int /*<<< orphan*/  (* cb ) (TYPE_4__*) ;struct TYPE_14__** sub; } ;
typedef  TYPE_1__ RPanelsMenuItem ;
typedef  TYPE_2__ RPanelsMenu ;
typedef  TYPE_3__ RPanels ;
typedef  TYPE_4__ RCore ;

/* Variables and functions */
 int COUNT (char**) ; 
 int /*<<< orphan*/  PANEL_MODE_MENU ; 
 int /*<<< orphan*/  __clear_panels_menu (TYPE_4__*) ; 
 int /*<<< orphan*/  __handle_tab_new (TYPE_4__*) ; 
 int /*<<< orphan*/  __handle_tab_nth (TYPE_4__*,char) ; 
 int /*<<< orphan*/  __set_mode (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_4__*,int,int) ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_word_from_canvas (TYPE_4__*,TYPE_3__*,int,int) ; 
 char** menus ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 

bool __handle_mouse_on_top (RCore *core, int x, int y) {
	RPanels *panels = core->panels;
	char *word = get_word_from_canvas (core, panels, x, y);
	int i;
	for (i = 0; i < COUNT (menus); i++) {
		if (!strcmp (word, menus[i])) {
			__set_mode (core, PANEL_MODE_MENU);
			__clear_panels_menu (core);
			RPanelsMenu *menu = panels->panels_menu;
			RPanelsMenuItem *parent = menu->history[menu->depth - 1];
			parent->selectedIndex = i;
			RPanelsMenuItem *child = parent->sub[parent->selectedIndex];
			(void)(child->cb (core));
			__set_refresh_all (core, false, false);
			free (word);
			return true;
		}
	}
	if (!strcmp (word, "Tab")) {
		__handle_tab_new (core);
		free (word);
		return true;
	}
	if (word[0] == '[' && word[1] && word[2] == ']') {
		return true;
	}
	if (atoi (word)) {
		__handle_tab_nth (core, word[0]);
		return true;
	}
	return false;
}