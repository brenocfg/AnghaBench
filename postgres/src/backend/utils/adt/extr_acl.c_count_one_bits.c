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
typedef  int AclMode ;

/* Variables and functions */

__attribute__((used)) static int
count_one_bits(AclMode mask)
{
	int			nbits = 0;

	/* this code relies on AclMode being an unsigned type */
	while (mask)
	{
		if (mask & 1)
			nbits++;
		mask >>= 1;
	}
	return nbits;
}