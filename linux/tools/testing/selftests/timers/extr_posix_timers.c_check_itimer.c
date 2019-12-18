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
struct timeval {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tv_sec; } ;
struct itimerval {TYPE_1__ it_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY ; 
 int ITIMER_PROF ; 
 int ITIMER_REAL ; 
 int ITIMER_VIRTUAL ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SIGPROF ; 
 int /*<<< orphan*/  SIGVTALRM ; 
 int /*<<< orphan*/  check_diff (struct timeval,struct timeval) ; 
 scalar_t__ done ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idle_loop () ; 
 int /*<<< orphan*/  kernel_loop () ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int setitimer (int,struct itimerval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sig_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  user_loop () ; 

__attribute__((used)) static int check_itimer(int which)
{
	int err;
	struct timeval start, end;
	struct itimerval val = {
		.it_value.tv_sec = DELAY,
	};

	printf("Check itimer ");

	if (which == ITIMER_VIRTUAL)
		printf("virtual... ");
	else if (which == ITIMER_PROF)
		printf("prof... ");
	else if (which == ITIMER_REAL)
		printf("real... ");

	fflush(stdout);

	done = 0;

	if (which == ITIMER_VIRTUAL)
		signal(SIGVTALRM, sig_handler);
	else if (which == ITIMER_PROF)
		signal(SIGPROF, sig_handler);
	else if (which == ITIMER_REAL)
		signal(SIGALRM, sig_handler);

	err = gettimeofday(&start, NULL);
	if (err < 0) {
		perror("Can't call gettimeofday()\n");
		return -1;
	}

	err = setitimer(which, &val, NULL);
	if (err < 0) {
		perror("Can't set timer\n");
		return -1;
	}

	if (which == ITIMER_VIRTUAL)
		user_loop();
	else if (which == ITIMER_PROF)
		kernel_loop();
	else if (which == ITIMER_REAL)
		idle_loop();

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