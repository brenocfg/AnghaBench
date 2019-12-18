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
struct timespec {long tv_nsec; long tv_sec; } ;
typedef  long int64_t ;

/* Variables and functions */
 long MPMIN (long,int) ; 
 int /*<<< orphan*/  get_realtime (struct timespec*) ; 
 long mp_time_us () ; 

struct timespec mp_time_us_to_timespec(int64_t time_us)
{
    struct timespec ts;
    get_realtime(&ts);
    // We don't know what time source mp_time_us() uses, but usually it's not
    // CLOCK_REALTIME - so we have to remap the times.
    int64_t unow = mp_time_us();
    int64_t diff_us = time_us - unow;
    int64_t diff_secs = diff_us / (1000L * 1000L);
    long diff_nsecs = (diff_us - diff_secs * (1000L * 1000L)) * 1000L;
    if (diff_nsecs < 0) {
        diff_secs -= 1;
        diff_nsecs += 1000000000L;
    }
    if (diff_nsecs + ts.tv_nsec >= 1000000000UL) {
        diff_secs += 1;
        diff_nsecs -= 1000000000UL;
    }
    // OSX can't deal with large timeouts. Also handles tv_sec/time_t overflows.
    diff_secs = MPMIN(diff_secs, 10000000);
    ts.tv_sec += diff_secs;
    ts.tv_nsec += diff_nsecs;
    return ts;
}