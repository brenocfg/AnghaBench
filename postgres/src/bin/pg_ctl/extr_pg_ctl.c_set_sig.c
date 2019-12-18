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
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  do_advice () ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  progname ; 
 int /*<<< orphan*/  sig ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  write_stderr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
set_sig(char *signame)
{
	if (strcmp(signame, "HUP") == 0)
		sig = SIGHUP;
	else if (strcmp(signame, "INT") == 0)
		sig = SIGINT;
	else if (strcmp(signame, "QUIT") == 0)
		sig = SIGQUIT;
	else if (strcmp(signame, "ABRT") == 0)
		sig = SIGABRT;
	else if (strcmp(signame, "KILL") == 0)
		sig = SIGKILL;
	else if (strcmp(signame, "TERM") == 0)
		sig = SIGTERM;
	else if (strcmp(signame, "USR1") == 0)
		sig = SIGUSR1;
	else if (strcmp(signame, "USR2") == 0)
		sig = SIGUSR2;
	else
	{
		write_stderr(_("%s: unrecognized signal name \"%s\"\n"), progname, signame);
		do_advice();
		exit(1);
	}
}