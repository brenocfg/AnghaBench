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
typedef  scalar_t__ packet_id_type ;

/* Variables and functions */

__attribute__((used)) static inline bool
reliable_pid_in_range2(const packet_id_type test,
                       const packet_id_type base,
                       const unsigned int extent)
{
    if (base + extent >= base)
    {
        if (test < base + extent)
        {
            return true;
        }
    }
    else
    {
        if ((test+0x80000000u) < (base+0x80000000u) + extent)
        {
            return true;
        }
    }

    return false;
}