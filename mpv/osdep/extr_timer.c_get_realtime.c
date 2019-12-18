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
struct timeval {unsigned long tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {unsigned long tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_realtime(struct timespec *out_ts)
{
#if defined(_POSIX_TIMERS) && _POSIX_TIMERS > 0
    clock_gettime(CLOCK_REALTIME, out_ts);
#else
    // OSX
    struct timeval tv;
    gettimeofday(&tv, NULL);
    out_ts->tv_sec = tv.tv_sec;
    out_ts->tv_nsec = tv.tv_usec * 1000UL;
#endif
}