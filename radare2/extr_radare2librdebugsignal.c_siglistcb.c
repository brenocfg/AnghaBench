#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int _mode; } ;
typedef  TYPE_1__ RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  DB ; 
 int R_DBG_SIGNAL_CONT ; 
 int R_DBG_SIGNAL_SKIP ; 
 scalar_t__ atoi (char const*) ; 
 int /*<<< orphan*/  r_cons_newline () ; 
 int /*<<< orphan*/  r_cons_printf (char*,char const*,char const*) ; 
 int /*<<< orphan*/  r_cons_strcat (char*) ; 
 int sdb_num_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static int siglistcb (void *p, const char *k, const char *v) {
	static char key[32] = "cfg.";
	RDebug *dbg = (RDebug *)p;
	int opt, mode = dbg->_mode;
	if (atoi (k) > 0) {
		strncpy (key + 4, k, 20);
		opt = sdb_num_get (DB, key, 0);
		if (opt) {
			r_cons_printf ("%s %s", k, v);
			if (opt & R_DBG_SIGNAL_CONT) {
				r_cons_strcat (" cont");
			}
			if (opt & R_DBG_SIGNAL_SKIP) {
				r_cons_strcat (" skip");
			}
			r_cons_newline ();
		} else {
			if (mode == 0) {
				r_cons_printf ("%s %s\n", k, v);
			}
		}
	}
	return 1;
}