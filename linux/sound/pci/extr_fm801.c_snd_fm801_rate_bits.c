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

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 unsigned int* rates ; 
 int /*<<< orphan*/  snd_BUG () ; 

__attribute__((used)) static unsigned short snd_fm801_rate_bits(unsigned int rate)
{
	unsigned int idx;

	for (idx = 0; idx < ARRAY_SIZE(rates); idx++)
		if (rates[idx] == rate)
			return idx;
	snd_BUG();
	return ARRAY_SIZE(rates) - 1;
}