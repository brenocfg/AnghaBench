#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct timeval {int tv_sec; int tv_usec; } ;
struct timespec {int tv_sec; int tv_nsec; } ;
struct TYPE_6__ {int denom; int numer; } ;
typedef  TYPE_1__ mach_timebase_info_data_t ;
struct TYPE_7__ {int QuadPart; } ;
typedef  TYPE_2__ LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  QueryPerformanceCounter (TYPE_2__*) ; 
 int /*<<< orphan*/  QueryPerformanceFrequency (TYPE_2__*) ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int gethrtime () ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int mach_absolute_time () ; 
 int /*<<< orphan*/  mach_timebase_info (TYPE_1__*) ; 
 scalar_t__ nn_slow (int) ; 

uint64_t nn_clock_ms (void)
{
#if defined NN_HAVE_WINDOWS

    LARGE_INTEGER tps;
    LARGE_INTEGER time;
    double tpms;

    QueryPerformanceFrequency (&tps);
    QueryPerformanceCounter (&time);
    tpms = (double) (tps.QuadPart / 1000);
    return (uint64_t) (time.QuadPart / tpms);

#elif defined NN_HAVE_OSX

    static mach_timebase_info_data_t nn_clock_timebase_info;
    uint64_t ticks;

    /*  If the global timebase info is not initialised yet, init it. */
    if (nn_slow (!nn_clock_timebase_info.denom))
        mach_timebase_info (&nn_clock_timebase_info);

    ticks = mach_absolute_time ();
    return ticks * nn_clock_timebase_info.numer /
        nn_clock_timebase_info.denom / 1000000;

#elif defined NN_HAVE_GETHRTIME

    return gethrtime () / 1000000;

#elif defined NN_HAVE_CLOCK_MONOTONIC

    int rc;
    struct timespec tv;

    rc = clock_gettime (CLOCK_MONOTONIC, &tv);
    errno_assert (rc == 0);
    return tv.tv_sec * (uint64_t) 1000 + tv.tv_nsec / 1000000;

#else

    int rc;
    struct timeval tv;

    /*  Gettimeofday is slow on some systems. Moreover, it's not necessarily
        monotonic. Thus, it's used as a last resort mechanism. */
    rc = gettimeofday (&tv, NULL);
    errno_assert (rc == 0);
    return tv.tv_sec * (uint64_t) 1000 + tv.tv_usec / 1000;

#endif
}