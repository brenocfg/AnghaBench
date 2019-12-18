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
 int atoi (char*) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_print (char*) ; 
 int /*<<< orphan*/  r_core_cmdf (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  r_fs_check (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ r_str_trim_ro (char*) ; 
 char* r_syscmd_tail (char*,int) ; 
 char* strchr (char*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int cmd_tail(void *data, const char *_input) { // "tail"
	char *input = strdup (_input);
	RCore *core = (RCore *)data;
	int lines = 5;
	char *arg = strchr (input, ' ');
	char *tmp, *count;
	if (arg) {
		arg = (char *)r_str_trim_ro (arg + 1); 	// contains "count filename"
		count = strchr (arg, ' ');
		if (count) {
			*count = 0;	// split the count and file name
			tmp = (char *)r_str_trim_ro (count + 1);
			lines = atoi (arg);
			arg = tmp;
		}
	}
	switch (*input) {
	case '?': // "tail?"
		eprintf ("Usage: tail [file] # to list last n lines in file\n");
		break;
	default: // "tail"
		if (!arg) {
			arg = "";
		}
		if (r_fs_check (core->fs, arg)) {
			r_core_cmdf (core, "md %s", arg);
		} else {
			char *res = r_syscmd_tail (arg, lines);
			if (res) {
				r_cons_print (res);
				free (res);
			}
		}
		break;
	}
	free (input);
	return 0;
}