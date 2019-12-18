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
 scalar_t__ debug ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int maxretries ; 
 int /*<<< orphan*/  pg_usleep (long) ; 
 int /*<<< orphan*/  restoreCommand ; 
 long sleeptime ; 
 int /*<<< orphan*/  stderr ; 
 int system (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
RestoreWALFileForRecovery(void)
{
	int			rc = 0;
	int			numretries = 0;

	if (debug)
	{
		fprintf(stderr, "running restore:      ");
		fflush(stderr);
	}

	while (numretries <= maxretries)
	{
		rc = system(restoreCommand);
		if (rc == 0)
		{
			if (debug)
			{
				fprintf(stderr, "OK\n");
				fflush(stderr);
			}
			return true;
		}
		pg_usleep(numretries++ * sleeptime * 1000000L);
	}

	/*
	 * Allow caller to add additional info
	 */
	if (debug)
		fprintf(stderr, "not restored\n");
	return false;
}