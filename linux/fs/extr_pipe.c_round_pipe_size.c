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
 unsigned long PAGE_SIZE ; 
 unsigned int roundup_pow_of_two (unsigned long) ; 

unsigned int round_pipe_size(unsigned long size)
{
	if (size > (1U << 31))
		return 0;

	/* Minimum pipe size, as required by POSIX */
	if (size < PAGE_SIZE)
		return PAGE_SIZE;

	return roundup_pow_of_two(size);
}