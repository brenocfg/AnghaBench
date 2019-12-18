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

int
tarChecksum(char *header)
{
	int			i,
				sum;

	/*
	 * Per POSIX, the checksum is the simple sum of all bytes in the header,
	 * treating the bytes as unsigned, and treating the checksum field (at
	 * offset 148) as though it contained 8 spaces.
	 */
	sum = 8 * ' ';				/* presumed value for checksum field */
	for (i = 0; i < 512; i++)
		if (i < 148 || i >= 156)
			sum += 0xFF & header[i];
	return sum;
}