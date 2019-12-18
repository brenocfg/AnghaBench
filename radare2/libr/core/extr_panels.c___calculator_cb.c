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

/* Variables and functions */
 char* __show_status_input (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_flush () ; 
 int /*<<< orphan*/  r_core_cmdf (int /*<<< orphan*/ *,char*,char*) ; 

int __calculator_cb(void *user) {
	RCore *core = (RCore *)user;
	for (;;) {
		char *s = __show_status_input (core, "> ");
		if (!s || !*s) {
			free (s);
			break;
		}
		r_core_cmdf (core, "? %s", s);
		r_cons_flush ();
		free (s);
	}
	return 0;
}