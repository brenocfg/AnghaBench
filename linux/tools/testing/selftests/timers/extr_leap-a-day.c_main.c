#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timer_t ;
typedef  int time_t ;
struct TYPE_8__ {int tv_sec; int /*<<< orphan*/  tv_usec; } ;
struct timex {scalar_t__ status; TYPE_4__ time; int /*<<< orphan*/  tai; void* modes; } ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct timespec {int tv_sec; int tv_nsec; } ;
struct TYPE_5__ {scalar_t__ sival_int; } ;
struct sigevent {int sigev_signo; TYPE_1__ sigev_value; int /*<<< orphan*/  sigev_notify; } ;
struct sigaction {int /*<<< orphan*/  sa_handler; scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; } ;
struct TYPE_7__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct TYPE_6__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct itimerspec {TYPE_3__ it_interval; TYPE_2__ it_value; } ;
typedef  int /*<<< orphan*/  se ;

/* Variables and functions */
 void* ADJ_STATUS ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  CLOCK_TAI ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  SIGEV_SIGNAL ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGKILL ; 
 int SIGRTMAX ; 
 scalar_t__ STA_DEL ; 
 scalar_t__ STA_INS ; 
 int /*<<< orphan*/  TIMER_ABSTIME ; 
 int adjtimex (struct timex*) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_time_state () ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ clock_nanosleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ *) ; 
 char* ctime (int*) ; 
 int /*<<< orphan*/  ctime_r (int*,char*) ; 
 scalar_t__ error_found ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  handler ; 
 int ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 int /*<<< orphan*/  memset (struct sigevent*,int /*<<< orphan*/ ,int) ; 
 int next_leap ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  settimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigalarm ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  test_hrtimer_failure () ; 
 char* time_state_str (int) ; 
 int timer_create (int /*<<< orphan*/ ,struct sigevent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerspec*,int /*<<< orphan*/ *) ; 

int main(int argc, char **argv)
{
	timer_t tm1;
	struct itimerspec its1;
	struct sigevent se;
	struct sigaction act;
	int signum = SIGRTMAX;
	int settime = 1;
	int tai_time = 0;
	int insert = 1;
	int iterations = 10;
	int opt;

	/* Process arguments */
	while ((opt = getopt(argc, argv, "sti:")) != -1) {
		switch (opt) {
		case 'w':
			printf("Only setting leap-flag, not changing time. It could take up to a day for leap to trigger.\n");
			settime = 0;
			break;
		case 'i':
			iterations = atoi(optarg);
			break;
		case 't':
			tai_time = 1;
			break;
		default:
			printf("Usage: %s [-w] [-i <iterations>]\n", argv[0]);
			printf("	-w: Set flag and wait for leap second each iteration");
			printf("	    (default sets time to right before leapsecond)\n");
			printf("	-i: Number of iterations (-1 = infinite, default is 10)\n");
			printf("	-t: Print TAI time\n");
			exit(-1);
		}
	}

	/* Make sure TAI support is present if -t was used */
	if (tai_time) {
		struct timespec ts;

		if (clock_gettime(CLOCK_TAI, &ts)) {
			printf("System doesn't support CLOCK_TAI\n");
			ksft_exit_fail();
		}
	}

	signal(SIGINT, handler);
	signal(SIGKILL, handler);

	/* Set up timer signal handler: */
	sigfillset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = sigalarm;
	sigaction(signum, &act, NULL);

	if (iterations < 0)
		printf("This runs continuously. Press ctrl-c to stop\n");
	else
		printf("Running for %i iterations. Press ctrl-c to stop\n", iterations);

	printf("\n");
	while (1) {
		int ret;
		struct timespec ts;
		struct timex tx;
		time_t now;

		/* Get the current time */
		clock_gettime(CLOCK_REALTIME, &ts);

		/* Calculate the next possible leap second 23:59:60 GMT */
		next_leap = ts.tv_sec;
		next_leap += 86400 - (next_leap % 86400);

		if (settime) {
			struct timeval tv;

			tv.tv_sec = next_leap - 10;
			tv.tv_usec = 0;
			settimeofday(&tv, NULL);
			printf("Setting time to %s", ctime(&tv.tv_sec));
		}

		/* Reset NTP time state */
		clear_time_state();

		/* Set the leap second insert flag */
		tx.modes = ADJ_STATUS;
		if (insert)
			tx.status = STA_INS;
		else
			tx.status = STA_DEL;
		ret = adjtimex(&tx);
		if (ret < 0) {
			printf("Error: Problem setting STA_INS/STA_DEL!: %s\n",
							time_state_str(ret));
			return ksft_exit_fail();
		}

		/* Validate STA_INS was set */
		tx.modes = 0;
		ret = adjtimex(&tx);
		if (tx.status != STA_INS && tx.status != STA_DEL) {
			printf("Error: STA_INS/STA_DEL not set!: %s\n",
							time_state_str(ret));
			return ksft_exit_fail();
		}

		if (tai_time) {
			printf("Using TAI time,"
				" no inconsistencies should be seen!\n");
		}

		printf("Scheduling leap second for %s", ctime(&next_leap));

		/* Set up timer */
		printf("Setting timer for %ld -  %s", next_leap, ctime(&next_leap));
		memset(&se, 0, sizeof(se));
		se.sigev_notify = SIGEV_SIGNAL;
		se.sigev_signo = signum;
		se.sigev_value.sival_int = 0;
		if (timer_create(CLOCK_REALTIME, &se, &tm1) == -1) {
			printf("Error: timer_create failed\n");
			return ksft_exit_fail();
		}
		its1.it_value.tv_sec = next_leap;
		its1.it_value.tv_nsec = 0;
		its1.it_interval.tv_sec = 0;
		its1.it_interval.tv_nsec = 0;
		timer_settime(tm1, TIMER_ABSTIME, &its1, NULL);

		/* Wake up 3 seconds before leap */
		ts.tv_sec = next_leap - 3;
		ts.tv_nsec = 0;


		while (clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &ts, NULL))
			printf("Something woke us up, returning to sleep\n");

		/* Validate STA_INS is still set */
		tx.modes = 0;
		ret = adjtimex(&tx);
		if (tx.status != STA_INS && tx.status != STA_DEL) {
			printf("Something cleared STA_INS/STA_DEL, setting it again.\n");
			tx.modes = ADJ_STATUS;
			if (insert)
				tx.status = STA_INS;
			else
				tx.status = STA_DEL;
			ret = adjtimex(&tx);
		}

		/* Check adjtimex output every half second */
		now = tx.time.tv_sec;
		while (now < next_leap + 2) {
			char buf[26];
			struct timespec tai;
			int ret;

			tx.modes = 0;
			ret = adjtimex(&tx);

			if (tai_time) {
				clock_gettime(CLOCK_TAI, &tai);
				printf("%ld sec, %9ld ns\t%s\n",
						tai.tv_sec,
						tai.tv_nsec,
						time_state_str(ret));
			} else {
				ctime_r(&tx.time.tv_sec, buf);
				buf[strlen(buf)-1] = 0; /*remove trailing\n */

				printf("%s + %6ld us (%i)\t%s\n",
						buf,
						tx.time.tv_usec,
						tx.tai,
						time_state_str(ret));
			}
			now = tx.time.tv_sec;
			/* Sleep for another half second */
			ts.tv_sec = 0;
			ts.tv_nsec = NSEC_PER_SEC / 2;
			clock_nanosleep(CLOCK_MONOTONIC, 0, &ts, NULL);
		}
		/* Switch to using other mode */
		insert = !insert;

		/* Note if kernel has known hrtimer failure */
		test_hrtimer_failure();

		printf("Leap complete\n");
		if (error_found) {
			printf("Errors observed\n");
			clear_time_state();
			return ksft_exit_fail();
		}
		printf("\n");
		if ((iterations != -1) && !(--iterations))
			break;
	}

	clear_time_state();
	return ksft_exit_pass();
}