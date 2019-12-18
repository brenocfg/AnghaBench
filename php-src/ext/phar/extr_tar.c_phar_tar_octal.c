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
 int FAILURE ; 
 int SUCCESS ; 

__attribute__((used)) static int phar_tar_octal(char *buf, uint32_t val, int len) /* {{{ */
{
	char *p = buf;
	int s = len;

	p += len;		/* Start at the end and work backwards. */
	while (s-- > 0) {
		*--p = (char)('0' + (val & 7));
		val >>= 3;
	}

	if (val == 0)
		return SUCCESS;

	/* If it overflowed, fill field with max value. */
	while (len-- > 0)
		*p++ = '7';

	return FAILURE;
}