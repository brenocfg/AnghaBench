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
 char* LABEL_FORMAT ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  START_TIMER ; 
 int /*<<< orphan*/  STOP_TIMER ; 
 scalar_t__ XLOG_BLCKSZ ; 
 int XLOG_BLCKSZ_K ; 
 char* _ (char*) ; 
 int alarm_triggered ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filename ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ write (int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
test_non_sync(void)
{
	int			tmpfile,
				ops;

	/*
	 * Test a simple write without fsync
	 */
	printf(_("\nNon-sync'ed %dkB writes:\n"), XLOG_BLCKSZ_K);
	printf(LABEL_FORMAT, "write");
	fflush(stdout);

	START_TIMER;
	for (ops = 0; alarm_triggered == false; ops++)
	{
		if ((tmpfile = open(filename, O_RDWR, 0)) == -1)
			die("could not open output file");
		if (write(tmpfile, buf, XLOG_BLCKSZ) != XLOG_BLCKSZ)
			die("write failed");
		close(tmpfile);
	}
	STOP_TIMER;
}