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

__attribute__((used)) static inline int dn_check_idf(unsigned char **pptr, int *len, unsigned char max, unsigned char follow_on)
{
	unsigned char *ptr = *pptr;
	unsigned char flen = *ptr++;

	(*len)--;
	if (flen > max)
		return -1;
	if ((flen + follow_on) > *len)
		return -1;

	*len -= flen;
	*pptr = ptr + flen;
	return 0;
}