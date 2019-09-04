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
typedef  unsigned long long uint64_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t
next_power_of_two(uint64_t num)
{
    uint64_t power_of_two = 1;

    num++;

    while ((uint64_t)(1ULL << power_of_two) < num)
        power_of_two++;

    return (1ULL << power_of_two);
}