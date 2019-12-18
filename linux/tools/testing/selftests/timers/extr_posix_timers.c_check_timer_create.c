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
typedef  int /*<<< orphan*/  timer_t ;
struct timeval {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tv_sec; } ;
struct itimerspec {TYPE_1__ it_value; } ;

/* Variables and functions */
 int CLOCK_PROCESS_CPUTIME_ID ; 
 int CLOCK_THREAD_CPUTIME_ID ; 
 int /*<<< orphan*/  DELAY ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  check_diff (struct timeval,struct timeval) ; 
 scalar_t__ done ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sig_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int timer_create (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int timer_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerspec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_loop () ; 

__attribute__((used)) static int check_timer_create(int which)
{
	int err;
	timer_t id;
	struct timeval start, end;
	struct itimerspec val = {
		.it_value.tv_sec = DELAY,
	};

	printf("Check timer_create() ");
	if (which == CLOCK_THREAD_CPUTIME_ID) {
		printf("per thread... ");
	} else if (which == CLOCK_PROCESS_CPUTIME_ID) {
		printf("per process... ");
	}
	fflush(stdout);

	done = 0;
	err = timer_create(which, NULL, &id);
	if (err < 0) {
		perror("Can't create timer\n");
		return -1;
	}
	signal(SIGALRM, sig_handler);

	err = gettimeofday(&start, NULL);
	if (err < 0) {
		perror("Can't call gettimeofday()\n");
		return -1;
	}

	err = timer_settime(id, 0, &val, NULL);
	if (err < 0) {
		perror("Can't set timer\n");
		return -1;
	}

	user_loop();

	err = gettimeofday(&end, NULL);
	if (err < 0) {
		perror("Can't call gettimeofday()\n");
		return -1;
	}

	if (!check_diff(start, end))
		printf("[OK]\n");
	else
		printf("[FAIL]\n");

	return 0;
}