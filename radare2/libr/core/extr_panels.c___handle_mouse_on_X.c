#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {TYPE_3__* panels; } ;
struct TYPE_24__ {TYPE_2__* view; } ;
struct TYPE_23__ {int /*<<< orphan*/  almighty_db; } ;
struct TYPE_21__ {int y; int x; int w; } ;
struct TYPE_22__ {TYPE_1__ pos; } ;
typedef  TYPE_3__ RPanels ;
typedef  TYPE_4__ RPanel ;
typedef  TYPE_5__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_MODE_DEFAULT ; 
 int /*<<< orphan*/  __create_almighty (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dismantle_del_panel (TYPE_5__*,TYPE_4__*,int const) ; 
 int /*<<< orphan*/  __get_cur_panel (TYPE_3__*) ; 
 TYPE_4__* __get_panel (TYPE_3__*,int const) ; 
 int __get_panel_idx_in_pos (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  __set_curnode (TYPE_5__*,int const) ; 
 int /*<<< orphan*/  __set_mode (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  __toggle_cache (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_word_from_canvas (TYPE_5__*,TYPE_3__*,int,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static bool __handle_mouse_on_X(RCore *core, int x, int y) {
	RPanels *panels = core->panels;
	const int idx = __get_panel_idx_in_pos (core, x, y);
	char *word = get_word_from_canvas (core, panels, x, y);
	if (idx == -1) {
		return false;
	}
	RPanel *ppos = __get_panel(panels, idx);
	const int TITLE_Y = ppos->view->pos.y + 2;
	if (y == TITLE_Y && strcmp (word, " X ")) {
		int fx = ppos->view->pos.x;
		int fX = fx + ppos->view->pos.w;
		__set_curnode (core, idx);
		__set_refresh_all (core, true, true);
		if (x > (fX - 13) && x < fX) {
			__toggle_cache (core, __get_cur_panel (panels));
		} else if (x > fx && x < (fx + 5)) {
			__dismantle_del_panel (core, ppos, idx);
		} else {
			__create_almighty (core, __get_panel (panels, 0), panels->almighty_db);
			__set_mode (core, PANEL_MODE_DEFAULT);
		}
		__set_refresh_all (core, false, false);
		free (word);
		return true;
	}
	free (word);
	return false;
}