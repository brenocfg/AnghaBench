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
 scalar_t__ test_bit (int /*<<< orphan*/ ,unsigned long const*) ; 

__attribute__((used)) static unsigned int count_bits(const unsigned long *addr,
				unsigned int offset, unsigned int len)
{
	unsigned int end = offset + len, sum = 0;

	while (offset < end) {
		if (test_bit(offset++, addr))
			++sum;
	}
	return sum;
}