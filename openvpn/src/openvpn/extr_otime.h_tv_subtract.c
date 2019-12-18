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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */
 int constrain_int (scalar_t__,int const,int const) ; 

__attribute__((used)) static inline int
tv_subtract(const struct timeval *tv1, const struct timeval *tv2, const unsigned int max_seconds)
{
    const int max_usec = max_seconds * 1000000;
    const int sec_diff = tv1->tv_sec - tv2->tv_sec;

    if (sec_diff > ((int)max_seconds + 10))
    {
        return max_usec;
    }
    else if (sec_diff < -((int)max_seconds + 10))
    {
        return -max_usec;
    }
    return constrain_int(sec_diff * 1000000 + (tv1->tv_usec - tv2->tv_usec), -max_usec, max_usec);
}