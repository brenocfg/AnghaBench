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
 int code ; 
 int /*<<< orphan*/  command (char*,char const*,char const*) ; 
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

void do_chmod(int argc, const char *argv[])
{
	if (argc == 2) {
		printf("usage: %s mode file-name\n", argv[0]);
		(void) fflush(stdout);
		code = -1;
		return;
	}
	if (argc < 3) {
		(void) strcat(line, " ");
		printf("(mode and file-name) ");
		(void) fflush(stdout);
		(void) gets(&line[strlen(line)]);
		makeargv();
		argc = margc;
		argv = margv;
	}
	if (argc != 3) {
		printf("usage: %s mode file-name\n", argv[0]);
		(void) fflush(stdout);
		code = -1;
		return;
	}
	(void)command("SITE CHMOD %s %s", argv[1], argv[2]);
}