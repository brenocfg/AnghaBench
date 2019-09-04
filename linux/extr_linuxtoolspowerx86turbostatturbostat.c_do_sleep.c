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
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int exit_requested ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interval_ts ; 
 struct timeval interval_tv ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nanosleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  one_msec ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  stdin ; 

void do_sleep(void)
{
	struct timeval select_timeout;
	fd_set readfds;
	int retval;

	FD_ZERO(&readfds);
	FD_SET(0, &readfds);

	if (!isatty(fileno(stdin))) {
		nanosleep(&interval_ts, NULL);
		return;
	}

	select_timeout = interval_tv;
	retval = select(1, &readfds, NULL, NULL, &select_timeout);

	if (retval == 1) {
		switch (getc(stdin)) {
		case 'q':
			exit_requested = 1;
			break;
		}
		/* make sure this manually-invoked interval is at least 1ms long */
		nanosleep(&one_msec, NULL);
	}
}