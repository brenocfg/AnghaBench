#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_print (char*) ; 
 int /*<<< orphan*/  r_core_cmdf (TYPE_1__*,char*,char const*) ; 
 int /*<<< orphan*/  r_fs_check (int /*<<< orphan*/ ,char const*) ; 
 char* r_str_trim_ro (char const*) ; 
 char* r_syscmd_uniq (char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int cmd_uniq(void *data, const char *input) { // "uniq"
	RCore *core = (RCore *)data;
	const char *arg = strchr (input, ' ');
	if (arg) {
		arg = r_str_trim_ro (arg + 1);
	}
	switch (*input) {
	case '?': // "uniq?"
		eprintf ("Usage: uniq # uniq to list unique strings in file\n");
		break;
	default: // "uniq"
		if (!arg) {
			arg = "";
		}
		if (r_fs_check (core->fs, arg)) {
			r_core_cmdf (core, "md %s", arg);
		} else {
			char *res = r_syscmd_uniq (arg);
			if (res) {
				r_cons_print (res);
				free (res);
			}
		}
		break;
	}
	return 0;
}