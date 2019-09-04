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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static void SHADecode32(uint32_t *output, const unsigned char *input, unsigned int len)
{
	unsigned int i, j;

	for (i = 0, j = 0; j < len; i++, j += 4)
		output[i] = ((uint32_t) input[j + 3]) | (((uint32_t) input[j + 2]) << 8) |
			(((uint32_t) input[j + 1]) << 16) | (((uint32_t) input[j]) << 24);
}