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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int __hex2bin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hex2bin(uint8_t *dst, const char *src, size_t count)
{
	while (count--) {
		int hi = __hex2bin(*src++);
		int lo = __hex2bin(*src++);

		if ((hi < 0) || (lo < 0))
			return -1;
		*dst++ = (hi << 4) | lo;
	}
	return 0;
}