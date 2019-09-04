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
typedef  size_t uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 int spi_transfer16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_read_bytes(char *dst, size_t length, uint8_t *bytesRead)
{
	uint16_t rx;
	uint8_t size;
	uint8_t i;

	memset(dst, 0, length);
	*bytesRead = 0;

	rx = spi_transfer16(0);
	if (!(rx >> 8))
		return -EINVAL;

	size = rx & 0xff;

	if (size > length)
		return -EINVAL;

	for (i = 0; i < size; ++i) {
		rx = spi_transfer16(0);
		if (!(rx >> 8))
			return -EINVAL;

		dst[i] = rx & 0xff;
	}

	*bytesRead = i;

	return 0;
}