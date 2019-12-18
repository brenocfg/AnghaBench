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
typedef  int const uint32_t ;

/* Variables and functions */

__attribute__((used)) static int aac_get_sample_rate_index(uint32_t sample_rate)
{
    static const int srates[] = {
        92017, 75132, 55426, 46009, 37566, 27713,
        23004, 18783, 13856, 11502, 9391, 0
    };
    int i = 0;
    while (sample_rate < srates[i])
        i++;
    return i;
}