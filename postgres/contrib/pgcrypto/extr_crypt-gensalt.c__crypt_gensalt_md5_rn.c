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
 char* _crypt_itoa64 ; 

char *
_crypt_gensalt_md5_rn(unsigned long count,
					  const char *input, int size, char *output, int output_size)
{
	unsigned long value;

	if (size < 3 || output_size < 3 + 4 + 1 || (count && count != 1000))
	{
		if (output_size > 0)
			output[0] = '\0';
		return NULL;
	}

	output[0] = '$';
	output[1] = '1';
	output[2] = '$';
	value = (unsigned long) (unsigned char) input[0] |
		((unsigned long) (unsigned char) input[1] << 8) |
		((unsigned long) (unsigned char) input[2] << 16);
	output[3] = _crypt_itoa64[value & 0x3f];
	output[4] = _crypt_itoa64[(value >> 6) & 0x3f];
	output[5] = _crypt_itoa64[(value >> 12) & 0x3f];
	output[6] = _crypt_itoa64[(value >> 18) & 0x3f];
	output[7] = '\0';

	if (size >= 6 && output_size >= 3 + 4 + 4 + 1)
	{
		value = (unsigned long) (unsigned char) input[3] |
			((unsigned long) (unsigned char) input[4] << 8) |
			((unsigned long) (unsigned char) input[5] << 16);
		output[7] = _crypt_itoa64[value & 0x3f];
		output[8] = _crypt_itoa64[(value >> 6) & 0x3f];
		output[9] = _crypt_itoa64[(value >> 12) & 0x3f];
		output[10] = _crypt_itoa64[(value >> 18) & 0x3f];
		output[11] = '\0';
	}

	return output;
}