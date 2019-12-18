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
 unsigned long __memcpy_mcsafe (char*,char*,int) ; 

unsigned long mcsafe_handle_tail(char *to, char *from, unsigned len)
{
	for (; len; --len, to++, from++) {
		/*
		 * Call the assembly routine back directly since
		 * memcpy_mcsafe() may silently fallback to memcpy.
		 */
		unsigned long rem = __memcpy_mcsafe(to, from, 1);

		if (rem)
			break;
	}
	return len;
}