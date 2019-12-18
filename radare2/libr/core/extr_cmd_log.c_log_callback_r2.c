#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 char* expr2cmd (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_printf (char*,char*) ; 
 int /*<<< orphan*/  r_core_cmd (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int log_callback_r2 (RCore *core, int count, const char *line) {
	if (*line == ':') {
		char *cmd = expr2cmd (core->log, line);
		if (cmd) {
			r_cons_printf ("%s\n", cmd);
			r_core_cmd (core, cmd, 0);
			free (cmd);
		}
	}
	return 0;
}