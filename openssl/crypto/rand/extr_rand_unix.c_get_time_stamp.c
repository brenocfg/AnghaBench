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
typedef  int /*<<< orphan*/  uint64_t ;
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int /*<<< orphan*/  TWO32TO64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t get_time_stamp(void)
{
# if defined(OSSL_POSIX_TIMER_OKAY)
    {
        struct timespec ts;

        if (clock_gettime(CLOCK_REALTIME, &ts) == 0)
            return TWO32TO64(ts.tv_sec, ts.tv_nsec);
    }
# endif
# if defined(__unix__) \
     || (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L)
    {
        struct timeval tv;

        if (gettimeofday(&tv, NULL) == 0)
            return TWO32TO64(tv.tv_sec, tv.tv_usec);
    }
# endif
    return time(NULL);
}