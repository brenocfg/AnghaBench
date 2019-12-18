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

__attribute__((used)) static inline unsigned int shift_bits(unsigned int value,
				      unsigned int shift_from,
				      unsigned int shift_to,
				      unsigned int mask)
{
	if (shift_from < shift_to)
		return (value << (shift_to - shift_from)) & mask;
	else
		return (value >> (shift_from - shift_to)) & mask;
}