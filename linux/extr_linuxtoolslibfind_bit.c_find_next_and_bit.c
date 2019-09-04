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
 unsigned long _find_next_bit (unsigned long const*,unsigned long const*,unsigned long,unsigned long,unsigned long) ; 

unsigned long find_next_and_bit(const unsigned long *addr1,
		const unsigned long *addr2, unsigned long size,
		unsigned long offset)
{
	return _find_next_bit(addr1, addr2, size, offset, 0UL);
}