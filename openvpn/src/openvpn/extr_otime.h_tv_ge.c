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
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
tv_ge(const struct timeval *t1, const struct timeval *t2)
{
    if (t1->tv_sec > t2->tv_sec)
    {
        return true;
    }
    else if (t1->tv_sec < t2->tv_sec)
    {
        return false;
    }
    else
    {
        return t1->tv_usec >= t2->tv_usec;
    }
}