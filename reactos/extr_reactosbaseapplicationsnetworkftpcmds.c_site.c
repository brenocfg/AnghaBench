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
 int BUFSIZ ; 
 scalar_t__ PRELIM ; 
 int code ; 
 scalar_t__ command (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ getreply (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gets (char*) ; 
 char* line ; 
 int /*<<< orphan*/  makeargv () ; 
 int margc ; 
 char** margv ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 

void site(int argc, const char *argv[])
{
	int i;
	char buf[BUFSIZ];

	if (argc < 2) {
		(void) strcat(line, " ");
		printf("(arguments to SITE command) ");
		(void) fflush(stdout);
		(void) gets(&line[strlen(line)]);
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc < 2) {
		printf("usage: %s line-to-send\n", argv[0]);
		(void) fflush(stdout);
		code = -1;
		return;
	}
	(void) strcpy(buf, "SITE ");
	(void) strcat(buf, argv[1]);
	for (i = 2; i < argc; i++) {
		(void) strcat(buf, " ");
		(void) strcat(buf, argv[i]);
	}
	if (command(buf) == PRELIM) {
		while (getreply(0) == PRELIM);
	}
}