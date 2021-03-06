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
typedef  int uint32_t ;

/* Variables and functions */

uint32_t mp_round_next_power_of_2(uint32_t v)
{
    for (int n = 0; n < 30; n++) {
        if ((1 << n) >= v)
            return 1 << n;
    }
    return 0;
}