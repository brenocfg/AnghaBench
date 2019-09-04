#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sigevent {int dummy; } ;
struct TYPE_2__ {int tv_sec; } ;
struct itimerspec {TYPE_1__ it_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_BOOTTIME_ALARM ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,...) ; 
 int /*<<< orphan*/  ksft_exit_skip (char*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 int timerfd_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int timerfd_settime (int,int /*<<< orphan*/ ,struct itimerspec*,int /*<<< orphan*/ *) ; 
 scalar_t__ write (int,char*,scalar_t__) ; 

void suspend(void)
{
	int power_state_fd;
	struct sigevent event = {};
	int timerfd;
	int err;
	struct itimerspec spec = {};

	if (getuid() != 0)
		ksft_exit_skip("Please run the test as root - Exiting.\n");

	power_state_fd = open("/sys/power/state", O_RDWR);
	if (power_state_fd < 0)
		ksft_exit_fail_msg(
			"open(\"/sys/power/state\") failed %s)\n",
			strerror(errno));

	timerfd = timerfd_create(CLOCK_BOOTTIME_ALARM, 0);
	if (timerfd < 0)
		ksft_exit_fail_msg("timerfd_create() failed\n");

	spec.it_value.tv_sec = 5;
	err = timerfd_settime(timerfd, 0, &spec, NULL);
	if (err < 0)
		ksft_exit_fail_msg("timerfd_settime() failed\n");

	if (write(power_state_fd, "mem", strlen("mem")) != strlen("mem"))
		ksft_exit_fail_msg("Failed to enter Suspend state\n");

	close(timerfd);
	close(power_state_fd);
}