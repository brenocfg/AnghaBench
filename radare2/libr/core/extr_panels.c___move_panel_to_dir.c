#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * panels; } ;
typedef  int /*<<< orphan*/  RPanels ;
typedef  int /*<<< orphan*/  RPanel ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __dismantle_panel (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __move_panel_to_down (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __move_panel_to_left (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __move_panel_to_right (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __move_panel_to_up (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_1__*,int,int) ; 
 int __show_status (TYPE_1__*,char*) ; 
 int r_cons_arrow_to_hjkl (int) ; 

void __move_panel_to_dir(RCore *core, RPanel *panel, int src) {
	RPanels *panels = core->panels;
	__dismantle_panel (panels, panel);
	int key = __show_status (core, "Move the current panel to direction (h/l): ");
	key = r_cons_arrow_to_hjkl (key);
	__set_refresh_all (core, false, true);
	switch (key) {
	case 'h':
		__move_panel_to_left (core, panel, src);
		break;
	case 'l':
		__move_panel_to_right (core, panel, src);
		break;
	case 'k':
		__move_panel_to_up (core, panel, src);
		break;
	case 'j':
		__move_panel_to_down (core, panel, src);
		break;
	default:
		break;
	}
}