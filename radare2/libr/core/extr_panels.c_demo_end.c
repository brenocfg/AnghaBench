#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  config; int /*<<< orphan*/  panels; } ;
struct TYPE_8__ {TYPE_1__* view; } ;
struct TYPE_7__ {int refresh; } ;
typedef  TYPE_2__ RPanel ;
typedef  TYPE_3__ RCore ;
typedef  int /*<<< orphan*/  RConsCanvas ;

/* Variables and functions */
 TYPE_2__* __get_cur_panel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __panels_refresh (TYPE_3__*) ; 
 int firstRun ; 
 int /*<<< orphan*/  free (char*) ; 
 int r_config_get_i (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_config_set_i (int /*<<< orphan*/ ,char*,int) ; 
 char* r_cons_canvas_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_clear00 () ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 int r_cons_get_size (int*) ; 
 int /*<<< orphan*/  r_cons_gotoxy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_cons_strcat (char*) ; 
 int /*<<< orphan*/  r_str_ansi_filter (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 char* r_str_scale (char*,int,int) ; 
 int /*<<< orphan*/  r_sys_usleep (int) ; 

__attribute__((used)) static void demo_end (RCore *core, RConsCanvas *can) {
	bool utf8 = r_config_get_i (core->config, "scr.utf8");
	r_config_set_i (core->config, "scr.utf8", 0);
	RPanel *cur = __get_cur_panel (core->panels);
	cur->view->refresh = true;
	firstRun= false;
	__panels_refresh (core);
	firstRun= true;
	r_config_set_i (core->config, "scr.utf8", utf8);
	char *s = r_cons_canvas_to_string (can);
	if (s) {
		// TODO drop utf8!!
		r_str_ansi_filter (s, NULL, NULL, -1);
		int i, h, w = r_cons_get_size (&h);
		for (i = h; i > 0; i--) {
			int H = i;
			char *r = r_str_scale (s, w, H);
			r_cons_clear00 ();
			r_cons_gotoxy (0, (h / 2) - (H / 2)); // center
			//r_cons_gotoxy (0, h-H); // bottom
			r_cons_strcat (r);
			r_cons_flush ();
			free (r);
			r_sys_usleep (3000);
		}
		r_sys_usleep (100000);
		free (s);
	}
}