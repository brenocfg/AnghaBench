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
 scalar_t__ ERROR ; 
 int code ; 
 scalar_t__ command (char*,char const*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gets (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * line ; 
 int /*<<< orphan*/  makeargv () ; 
 int margc ; 
 char** margv ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ *,char*) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ verbose ; 

void removedir(int argc, const char *argv[])
{

	if (argc < 2) {
		(void) strcat(line, " ");
		printf("(directory-name) ");
		(void) fflush(stdout);
		(void) gets(&line[strlen(line)]);
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
		printf("usage: %s directory-name\n", argv[0]);
		(void) fflush(stdout);
		code = -1;
		return;
	}
	if (command("RMD %s", argv[1]) == ERROR && code == 500) {
		if (verbose) {
			printf("RMD command not recognized, trying XRMD\n");
			(void) fflush(stdout);
		}
		(void) command("XRMD %s", argv[1]);
	}
}