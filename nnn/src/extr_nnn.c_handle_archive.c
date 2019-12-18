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

/* Variables and functions */
 size_t ATOOL ; 
 size_t BSDTAR ; 
 int /*<<< orphan*/  F_NORMAL ; 
 size_t TAR ; 
 int /*<<< orphan*/  TRUE ; 
 size_t UNZIP ; 
 int /*<<< orphan*/  exitcurses () ; 
 int /*<<< orphan*/  get_output (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ getutil (char*) ; 
 scalar_t__ is_suffix (char*,char*) ; 
 int /*<<< orphan*/  refresh () ; 
 int /*<<< orphan*/  spawn (char*,char*,char*,char const*,int /*<<< orphan*/ ) ; 
 char** utils ; 

__attribute__((used)) static void handle_archive(char *fpath, const char *dir, char op)
{
	char arg[] = "-tvf"; /* options for tar/bsdtar to list files */
	char *util;

	if (getutil(utils[ATOOL])) {
		util = utils[ATOOL];
		arg[1] = op;
		arg[2] = '\0';
	} else if (getutil(utils[BSDTAR])) {
		util = utils[BSDTAR];
		if (op == 'x')
			arg[1] = op;
	} else if (is_suffix(fpath, ".zip")) {
		util = utils[UNZIP];
		arg[1] = (op == 'l') ? 'v' /* verbose listing */ : '\0';
		arg[2] = '\0';
	} else {
		util = utils[TAR];
		if (op == 'x')
			arg[1] = op;
	}

	if (op == 'x') { /* extract */
		spawn(util, arg, fpath, dir, F_NORMAL);
	} else { /* list */
		exitcurses();
		get_output(NULL, 0, util, arg, fpath, TRUE);
		refresh();
	}
}