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
typedef  scalar_t__ interval_t ;

/* Variables and functions */

__attribute__((used)) static inline void
compute_earliest_wakeup(interval_t *earliest, interval_t seconds_from_now)
{
    if (seconds_from_now < *earliest)
    {
        *earliest = seconds_from_now;
    }
    if (*earliest < 0)
    {
        *earliest = 0;
    }
}