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
typedef  int BF_word ;

/* Variables and functions */

__attribute__((used)) static void BF_swap(BF_word *x, int count)
{
	static int endianness_check = 1;
	char *is_little_endian = (char *)&endianness_check;
	BF_word tmp;

	if (*is_little_endian)
	do {
		tmp = *x;
		tmp = (tmp << 16) | (tmp >> 16);
		*x++ = ((tmp & 0x00FF00FF) << 8) | ((tmp >> 8) & 0x00FF00FF);
	} while (--count);
}