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
typedef  int uint64_t ;
struct timespec {int tv_sec; int tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CLOCK_UPTIME_RAW ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int errno ; 
 int /*<<< orphan*/  printf (char*,int) ; 

uint64_t
pixie_gettime(void)
{
    int x;
    struct timespec tv;

#if defined(CLOCK_UPTIME_RAW)
    /* macOS: ignores time when suspended/sleep */
    x = clock_gettime(CLOCK_UPTIME_RAW, &tv);
//#elif defined(CLOCK_MONOTONIC_RAW)
//    x = clock_gettime(CLOCK_MONOTONIC_RAW, &tv);
#else
    x = clock_gettime(CLOCK_MONOTONIC, &tv);
#endif
    if (x != 0) {
        printf("clock_gettime() err %d\n", errno);
    }

    return tv.tv_sec * 1000000 + tv.tv_nsec/1000;
}