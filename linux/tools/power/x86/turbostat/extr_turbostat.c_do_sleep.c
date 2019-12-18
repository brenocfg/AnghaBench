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
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
#define  EOF 128 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int exit_requested ; 
 int getc (int /*<<< orphan*/ ) ; 
 int ignore_stdin ; 
 struct timespec interval_ts ; 
 struct timeval interval_tv ; 
 int /*<<< orphan*/  nanosleep (struct timespec*,int /*<<< orphan*/ *) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  stdin ; 

void do_sleep(void)
{
	struct timeval tout;
	struct timespec rest;
	fd_set readfds;
	int retval;

	FD_ZERO(&readfds);
	FD_SET(0, &readfds);

	if (ignore_stdin) {
		nanosleep(&interval_ts, NULL);
		return;
	}

	tout = interval_tv;
	retval = select(1, &readfds, NULL, NULL, &tout);

	if (retval == 1) {
		switch (getc(stdin)) {
		case 'q':
			exit_requested = 1;
			break;
		case EOF:
			/*
			 * 'stdin' is a pipe closed on the other end. There
			 * won't be any further input.
			 */
			ignore_stdin = 1;
			/* Sleep the rest of the time */
			rest.tv_sec = (tout.tv_sec + tout.tv_usec / 1000000);
			rest.tv_nsec = (tout.tv_usec % 1000000) * 1000;
			nanosleep(&rest, NULL);
		}
	}
}