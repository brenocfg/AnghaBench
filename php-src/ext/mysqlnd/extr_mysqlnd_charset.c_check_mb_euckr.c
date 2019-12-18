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
typedef  int zend_uchar ;

/* Variables and functions */
 scalar_t__ valid_euckr (char const) ; 

__attribute__((used)) static unsigned int check_mb_euckr(const char * const start, const char * const end)
{
	if (end - start <= 1) {
		return 0;	/* invalid length */
	}
	if (*(zend_uchar *)start < 0x80) {
		return 0;	/* invalid euckr character */
	}
	if (valid_euckr(start[1])) {
		return 2;
	}
	return 0;
}