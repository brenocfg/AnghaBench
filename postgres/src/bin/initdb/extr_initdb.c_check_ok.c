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
 char* _ (char*) ; 
 scalar_t__ caught_signal ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_errno ; 
 scalar_t__ output_failed ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_ok(void)
{
	if (caught_signal)
	{
		printf(_("caught signal\n"));
		fflush(stdout);
		exit(1);
	}
	else if (output_failed)
	{
		printf(_("could not write to child process: %s\n"),
			   strerror(output_errno));
		fflush(stdout);
		exit(1);
	}
	else
	{
		/* all seems well */
		printf(_("ok\n"));
		fflush(stdout);
	}
}