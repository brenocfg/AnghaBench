#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RCore ;
typedef  int /*<<< orphan*/  RConsCanvas ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* r_cons_canvas_to_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_cons_clear00 () ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 int r_cons_get_size (int*) ; 
 int /*<<< orphan*/  r_cons_gotoxy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_cons_strcat (char*) ; 
 int /*<<< orphan*/  r_str_ansi_filter (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 char* r_str_scale (char*,int,int) ; 
 int /*<<< orphan*/  r_sys_usleep (int) ; 

__attribute__((used)) static void demo_begin (RCore *core, RConsCanvas *can) {
	char *s = r_cons_canvas_to_string (can);
	if (s) {
		// TODO drop utf8!!
		r_str_ansi_filter (s, NULL, NULL, -1);
		int i, h, w = r_cons_get_size (&h);
		for (i = 0; i < 40; i+= (1 + (i/30))) {
			int H = i * ((double)h / 40);
			char *r = r_str_scale (s, w, H);
			r_cons_clear00 ();
			r_cons_gotoxy (0, (h / 2) - (H / 2));
			r_cons_strcat (r);
			r_cons_flush ();
			free (r);
			r_sys_usleep (3000);
		}
		free (s);
	}
}