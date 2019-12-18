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
struct timeval {int tv_sec; int tv_usec; } ;

/* Variables and functions */

__attribute__((used)) static inline void
tv_delta(struct timeval *dest, const struct timeval *t1, const struct timeval *t2)
{
    int sec = t2->tv_sec - t1->tv_sec;
    int usec = t2->tv_usec - t1->tv_usec;

    while (usec < 0)
    {
        usec += 1000000;
        sec -= 1;
    }

    if (sec < 0)
    {
        usec = sec = 0;
    }

    dest->tv_sec = sec;
    dest->tv_usec = usec;
}