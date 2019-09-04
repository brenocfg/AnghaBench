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
 unsigned int find_first_bit (unsigned long const*,unsigned int) ; 
 unsigned int find_next_bit (unsigned long const*,unsigned int,unsigned int) ; 

unsigned int bitmap_ord_to_pos(const unsigned long *buf, unsigned int ord, unsigned int nbits)
{
	unsigned int pos;

	for (pos = find_first_bit(buf, nbits);
	     pos < nbits && ord;
	     pos = find_next_bit(buf, nbits, pos + 1))
		ord--;

	return pos;
}