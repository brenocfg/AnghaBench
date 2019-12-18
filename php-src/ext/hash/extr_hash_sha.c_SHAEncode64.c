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
typedef  int uint64_t ;

/* Variables and functions */

__attribute__((used)) static void SHAEncode64(unsigned char *output, uint64_t *input, unsigned int len)
{
	unsigned int i, j;

	for (i = 0, j = 0; j < len; i++, j += 8) {
		output[j] = (unsigned char) ((input[i] >> 56) & 0xff);
		output[j + 1] = (unsigned char) ((input[i] >> 48) & 0xff);
		output[j + 2] = (unsigned char) ((input[i] >> 40) & 0xff);
		output[j + 3] = (unsigned char) ((input[i] >> 32) & 0xff);
		output[j + 4] = (unsigned char) ((input[i] >> 24) & 0xff);
		output[j + 5] = (unsigned char) ((input[i] >> 16) & 0xff);
		output[j + 6] = (unsigned char) ((input[i] >> 8) & 0xff);
		output[j + 7] = (unsigned char) (input[i] & 0xff);
	}
}