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
struct tnum {int mask; int value; } ;

/* Variables and functions */
 size_t min (size_t,size_t) ; 

int tnum_sbin(char *str, size_t size, struct tnum a)
{
	size_t n;

	for (n = 64; n; n--) {
		if (n < size) {
			if (a.mask & 1)
				str[n - 1] = 'x';
			else if (a.value & 1)
				str[n - 1] = '1';
			else
				str[n - 1] = '0';
		}
		a.mask >>= 1;
		a.value >>= 1;
	}
	str[min(size - 1, (size_t)64)] = 0;
	return 64;
}