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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_SYSTEM_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error (int /*<<< orphan*/ ,char*,...) ; 
 int pclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* wait_result_to_str (int) ; 

int
pclose_check(FILE *stream)
{
	int			exitstatus;
	char	   *reason;

	exitstatus = pclose(stream);

	if (exitstatus == 0)
		return 0;				/* all is well */

	if (exitstatus == -1)
	{
		/* pclose() itself failed, and hopefully set errno */
		log_error(errcode(ERRCODE_SYSTEM_ERROR),
				  _("pclose failed: %m"));
	}
	else
	{
		reason = wait_result_to_str(exitstatus);
		log_error(errcode(ERRCODE_SYSTEM_ERROR),
				  "%s", reason);
		pfree(reason);
	}
	return exitstatus;
}