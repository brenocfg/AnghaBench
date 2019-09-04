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

__attribute__((used)) static inline char *num_to_str(unsigned long num, char *buf, int len)
{
	unsigned int digit;

	/* put digits in buffer from back to front */
	buf += len - 1;
	*buf = 0;
	do {
		digit = num % 10;
		*(--buf) = digit + '0';
		num /= 10;
	} while (num > 0);

	return buf;
}