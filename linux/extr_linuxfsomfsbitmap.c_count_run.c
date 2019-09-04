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
 int find_next_bit (unsigned long*,int,int) ; 
 int min (int,int) ; 

__attribute__((used)) static int count_run(unsigned long **addr, int nbits,
		int addrlen, int bit, int max)
{
	int count = 0;
	int x;

	for (; addrlen > 0; addrlen--, addr++) {
		x = find_next_bit(*addr, nbits, bit);
		count += x - bit;

		if (x < nbits || count > max)
			return min(count, max);

		bit = 0;
	}
	return min(count, max);
}