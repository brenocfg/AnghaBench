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
struct TYPE_2__ {int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_print (char*) ; 
 int /*<<< orphan*/  r_fs_check (int /*<<< orphan*/ ,char const*) ; 
 char* r_str_trim_ro (char const*) ; 
 char* r_syscmd_join (char const*,char const*) ; 
 void* strchr (char const*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int cmd_join(void *data, const char *input) { // "join"
	RCore *core = (RCore *)data;
	char *tmp = strdup (input);
	const char *arg1 = strchr (tmp, ' ');
	if (!arg1) {
		goto beach;
	}
	arg1 = r_str_trim_ro (arg1);
	char *end = strchr (arg1, ' ');
	if (!end) {
		goto beach;
	}
	*end = '\0';
	const char *arg2 = end+1;
	if (!arg2) {
		goto beach;
	}
	arg2 = r_str_trim_ro (arg2);
	switch (*input) {
	case '?': // "join?"
		goto beach;
	default: // "join"
		if (!arg1) {
			arg1 = "";
		}
		if (!arg2) {
			arg2 = "";
		}
		if (!r_fs_check (core->fs, arg1) && !r_fs_check (core->fs, arg2)) {
			char *res = r_syscmd_join (arg1, arg2);
			if (res) {
				r_cons_print (res);
				free (res);
			}
		}
		break;
	}
	free (tmp);
	return 0;
beach:
	eprintf ("Usage: join [file1] [file2] # join the contents of the two files\n");
	free (tmp);
	return 0;
}