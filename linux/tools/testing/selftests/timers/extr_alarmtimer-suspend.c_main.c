#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timer_t ;
struct TYPE_5__ {scalar_t__ sival_int; } ;
struct sigevent {int sigev_signo; TYPE_1__ sigev_value; int /*<<< orphan*/  sigev_notify; } ;
struct sigaction {int /*<<< orphan*/  sa_handler; scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; } ;
struct TYPE_6__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_7__ {int /*<<< orphan*/  tv_sec; int /*<<< orphan*/  tv_nsec; } ;
struct itimerspec {TYPE_2__ it_interval; TYPE_3__ it_value; } ;
typedef  int /*<<< orphan*/  se ;

/* Variables and functions */
 scalar_t__ CLOCK_BOOTTIME_ALARM ; 
 scalar_t__ CLOCK_REALTIME_ALARM ; 
 int /*<<< orphan*/  SIGEV_SIGNAL ; 
 int SIGRTMAX ; 
 int SUSPEND_SECS ; 
 int /*<<< orphan*/  TIMER_ABSTIME ; 
 scalar_t__ alarm_clock_id ; 
 int alarmcount ; 
 int /*<<< orphan*/  clock_gettime (scalar_t__,TYPE_3__*) ; 
 char* clockstring (scalar_t__) ; 
 scalar_t__ final_ret ; 
 int ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 int /*<<< orphan*/  memset (struct sigevent*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigalarm ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 TYPE_3__ start_time ; 
 int system (char*) ; 
 int timer_create (scalar_t__,struct sigevent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerspec*,struct itimerspec*) ; 

int main(void)
{
	timer_t tm1;
	struct itimerspec its1, its2;
	struct sigevent se;
	struct sigaction act;
	int signum = SIGRTMAX;

	/* Set up signal handler: */
	sigfillset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = sigalarm;
	sigaction(signum, &act, NULL);

	/* Set up timer: */
	memset(&se, 0, sizeof(se));
	se.sigev_notify = SIGEV_SIGNAL;
	se.sigev_signo = signum;
	se.sigev_value.sival_int = 0;

	for (alarm_clock_id = CLOCK_REALTIME_ALARM;
			alarm_clock_id <= CLOCK_BOOTTIME_ALARM;
			alarm_clock_id++) {

		alarmcount = 0;
		if (timer_create(alarm_clock_id, &se, &tm1) == -1) {
			printf("timer_create failed, %s unsupported?\n",
					clockstring(alarm_clock_id));
			break;
		}

		clock_gettime(alarm_clock_id, &start_time);
		printf("Start time (%s): %ld:%ld\n", clockstring(alarm_clock_id),
				start_time.tv_sec, start_time.tv_nsec);
		printf("Setting alarm for every %i seconds\n", SUSPEND_SECS);
		its1.it_value = start_time;
		its1.it_value.tv_sec += SUSPEND_SECS;
		its1.it_interval.tv_sec = SUSPEND_SECS;
		its1.it_interval.tv_nsec = 0;

		timer_settime(tm1, TIMER_ABSTIME, &its1, &its2);

		while (alarmcount < 5)
			sleep(1); /* First 5 alarms, do nothing */

		printf("Starting suspend loops\n");
		while (alarmcount < 10) {
			int ret;

			sleep(3);
			ret = system("echo mem > /sys/power/state");
			if (ret)
				break;
		}
		timer_delete(tm1);
	}
	if (final_ret)
		return ksft_exit_fail();
	return ksft_exit_pass();
}