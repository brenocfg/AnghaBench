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
typedef  int u8 ;

/* Variables and functions */
 int hex_to_bin (char) ; 

__attribute__((used)) static bool unescape_hex(char **src, char **dst)
{
	char *p = *dst, *q = *src;
	int digit;
	u8 num;

	if (*q++ != 'x')
		return false;

	num = digit = hex_to_bin(*q++);
	if (digit < 0)
		return false;

	digit = hex_to_bin(*q);
	if (digit >= 0) {
		q++;
		num = (num << 4) | digit;
	}
	*p = num;
	*dst += 1;
	*src = q;
	return true;
}