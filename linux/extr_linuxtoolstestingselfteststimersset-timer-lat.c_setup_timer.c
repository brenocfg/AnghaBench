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
struct sigevent {TYPE_1__ sigev_value; int /*<<< orphan*/  sigev_signo; int /*<<< orphan*/  sigev_notify; } ;
struct TYPE_6__ {int tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_7__ {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct itimerspec {TYPE_2__ it_interval; TYPE_3__ it_value; } ;
typedef  int /*<<< orphan*/  se ;

/* Variables and functions */
 int CLOCK_BOOTTIME_ALARM ; 
 int CLOCK_REALTIME_ALARM ; 
 int /*<<< orphan*/  SIGEV_SIGNAL ; 
 int /*<<< orphan*/  SIGRTMAX ; 
 scalar_t__ TIMER_SECS ; 
 scalar_t__ alarmcount ; 
 int /*<<< orphan*/  clock_gettime (int,TYPE_3__*) ; 
 char* clockstring (int) ; 
 scalar_t__ max_latency_ns ; 
 int /*<<< orphan*/  memset (struct sigevent*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 TYPE_3__ start_time ; 
 int timer_create (int,struct sigevent*,int /*<<< orphan*/ *) ; 
 scalar_t__ timer_fired_early ; 
 int timer_settime (int /*<<< orphan*/ ,int,struct itimerspec*,struct itimerspec*) ; 

int setup_timer(int clock_id, int flags, int interval, timer_t *tm1)
{
	struct sigevent se;
	struct itimerspec its1, its2;
	int err;

	/* Set up timer: */
	memset(&se, 0, sizeof(se));
	se.sigev_notify = SIGEV_SIGNAL;
	se.sigev_signo = SIGRTMAX;
	se.sigev_value.sival_int = 0;

	max_latency_ns = 0;
	alarmcount = 0;
	timer_fired_early = 0;

	err = timer_create(clock_id, &se, tm1);
	if (err) {
		if ((clock_id == CLOCK_REALTIME_ALARM) ||
		    (clock_id == CLOCK_BOOTTIME_ALARM)) {
			printf("%-22s %s missing CAP_WAKE_ALARM?    : [UNSUPPORTED]\n",
					clockstring(clock_id),
					flags ? "ABSTIME":"RELTIME");
			/* Indicate timer isn't set, so caller doesn't wait */
			return 1;
		}
		printf("%s - timer_create() failed\n", clockstring(clock_id));
		return -1;
	}

	clock_gettime(clock_id, &start_time);
	if (flags) {
		its1.it_value = start_time;
		its1.it_value.tv_sec += TIMER_SECS;
	} else {
		its1.it_value.tv_sec = TIMER_SECS;
		its1.it_value.tv_nsec = 0;
	}
	its1.it_interval.tv_sec = interval;
	its1.it_interval.tv_nsec = 0;

	err = timer_settime(*tm1, flags, &its1, &its2);
	if (err) {
		printf("%s - timer_settime() failed\n", clockstring(clock_id));
		return -1;
	}

	return 0;
}