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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */

__attribute__((used)) static unsigned long add_csum_hword(const uint16_t *start, int num_u16)
{
	unsigned long sum = 0;
	int i;

	for (i = 0; i < num_u16; i++)
		sum += start[i];

	return sum;
}