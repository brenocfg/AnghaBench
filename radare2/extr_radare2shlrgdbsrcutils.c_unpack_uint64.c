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
 int hex2int (int /*<<< orphan*/ ) ; 

uint64_t unpack_uint64(char *buff, int len) {
	int nibble;
	uint64_t retval = 0;
	while (len) {
		nibble = hex2int (*buff++);
		retval |= nibble;
		len--;
		if (len) {
			retval = retval << 4;
		}
	}
	return retval;
}