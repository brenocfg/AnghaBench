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
typedef  int wchar_t ;
typedef  scalar_t__ unicode_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAX_WCHAR_T ; 
 int utf8_to_utf32 (unsigned char const*,int,scalar_t__*) ; 

__attribute__((used)) static int char2uni(const unsigned char *rawstring, int boundlen, wchar_t *uni)
{
	int n;
	unicode_t u;

	n = utf8_to_utf32(rawstring, boundlen, &u);
	if (n < 0 || u > MAX_WCHAR_T) {
		*uni = 0x003f;	/* ? */
		return -EINVAL;
	}
	*uni = (wchar_t) u;
	return n;
}