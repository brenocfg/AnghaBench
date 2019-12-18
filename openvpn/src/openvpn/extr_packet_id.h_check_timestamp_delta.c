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
typedef  scalar_t__ const time_t ;

/* Variables and functions */
 scalar_t__ now ; 

__attribute__((used)) static inline bool
check_timestamp_delta(time_t remote, unsigned int max_delta)
{
    unsigned int abs;
    const time_t local_now = now;

    if (local_now >= remote)
    {
        abs = local_now - remote;
    }
    else
    {
        abs = remote - local_now;
    }
    return abs <= max_delta;
}