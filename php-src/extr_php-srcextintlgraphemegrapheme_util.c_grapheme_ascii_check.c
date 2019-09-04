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
typedef  int zend_long ;

/* Variables and functions */

zend_long grapheme_ascii_check(const unsigned char *day, size_t len)
{
	int ret_len = len;
	while ( len-- ) {
	if ( *day++ > 0x7f || (*day == '\n' && *(day - 1) == '\r') )
		return -1;
	}

	return ret_len;
}