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
typedef  int usec_t ;
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  suseconds_t ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_SYSTEM ; 
 scalar_t__ EINTR ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,int) ; 
 scalar_t__ likely (int) ; 
 int nanosleep (struct timespec*,struct timespec*) ; 
 scalar_t__ unlikely (int) ; 
 int usleep (int) ; 

int sleep_usec(usec_t usec) {

#ifndef NETDATA_WITH_USLEEP
    // we expect microseconds (1.000.000 per second)
    // but timespec is nanoseconds (1.000.000.000 per second)
    struct timespec rem, req = {
            .tv_sec = (time_t) (usec / 1000000),
            .tv_nsec = (suseconds_t) ((usec % 1000000) * 1000)
    };

    while (nanosleep(&req, &rem) == -1) {
        if (likely(errno == EINTR)) {
            debug(D_SYSTEM, "nanosleep() interrupted (while sleeping for %llu microseconds).", usec);
            req.tv_sec = rem.tv_sec;
            req.tv_nsec = rem.tv_nsec;
        } else {
            error("Cannot nanosleep() for %llu microseconds.", usec);
            break;
        }
    }

    return 0;
#else
    int ret = usleep(usec);
    if(unlikely(ret == -1 && errno == EINVAL)) {
        // on certain systems, usec has to be up to 999999
        if(usec > 999999) {
            int counter = usec / 999999;
            while(counter--)
                usleep(999999);

            usleep(usec % 999999);
        }
        else {
            error("Cannot usleep() for %llu microseconds.", usec);
            return ret;
        }
    }

    if(ret != 0)
        error("usleep() failed for %llu microseconds.", usec);

    return ret;
#endif
}