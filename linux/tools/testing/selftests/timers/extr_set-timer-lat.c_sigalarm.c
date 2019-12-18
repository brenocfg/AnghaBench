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
struct timespec {int dummy; } ;

/* Variables and functions */
 long long NSEC_PER_SEC ; 
 long long TIMER_SECS ; 
 long long alarmcount ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  clock_id ; 
 long long max_latency_ns ; 
 int /*<<< orphan*/  start_time ; 
 int timer_fired_early ; 
 long long timespec_sub (int /*<<< orphan*/ ,struct timespec) ; 

void sigalarm(int signo)
{
	long long delta_ns;
	struct timespec ts;

	clock_gettime(clock_id, &ts);
	alarmcount++;

	delta_ns = timespec_sub(start_time, ts);
	delta_ns -= NSEC_PER_SEC * TIMER_SECS * alarmcount;

	if (delta_ns < 0)
		timer_fired_early = 1;

	if (delta_ns > max_latency_ns)
		max_latency_ns = delta_ns;
}