#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_2__* print; int /*<<< orphan*/ * panels; } ;
struct TYPE_20__ {TYPE_3__* view; TYPE_1__* model; } ;
struct TYPE_19__ {int refresh; } ;
struct TYPE_18__ {int /*<<< orphan*/  cur_enabled; } ;
struct TYPE_17__ {int cache; } ;
typedef  int /*<<< orphan*/  RPanels ;
typedef  TYPE_4__ RPanel ;
typedef  TYPE_5__ RCore ;

/* Variables and functions */
 TYPE_4__* __get_cur_panel (int /*<<< orphan*/ *) ; 
 scalar_t__ __is_abnormal_cursor_type (TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ __is_normal_cursor_type (TYPE_4__*) ; 
 int /*<<< orphan*/  __reset_scroll_pos (TYPE_4__*) ; 
 int /*<<< orphan*/  __set_cmd_str_cache (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_cursor (TYPE_5__*,int) ; 
 int /*<<< orphan*/  __show_status (TYPE_5__*,char*) ; 
 scalar_t__ __show_status_yesno (TYPE_5__*,int,char*) ; 

void __activate_cursor(RCore *core) {
	RPanels *panels = core->panels;
	RPanel *cur = __get_cur_panel (panels);
	if (__is_normal_cursor_type (cur) || __is_abnormal_cursor_type (core, cur)) {
		if (cur->model->cache) {
			if (__show_status_yesno (core, 1, "You need to turn off cache to use cursor. Turn off now?(Y/n)")) {
				cur->model->cache = false;
				__set_cmd_str_cache (core, cur, NULL);
				(void)__show_status (core, "Cache is off and cursor is on");
				__set_cursor (core, !core->print->cur_enabled);
				cur->view->refresh = true;
				__reset_scroll_pos (cur);
			} else {
				(void)__show_status (core, "You can always toggle cache by \'&\' key");
			}
			return;
		}
		__set_cursor (core, !core->print->cur_enabled);
		cur->view->refresh = true;
	} else {
		(void)__show_status (core, "Cursor is not available for the current panel.");
	}
}