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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  TOMOYO_VALUE_TYPE_DECIMAL ; 
 int /*<<< orphan*/  TOMOYO_VALUE_TYPE_HEXADECIMAL ; 
 int /*<<< orphan*/  TOMOYO_VALUE_TYPE_INVALID ; 
 int /*<<< orphan*/  TOMOYO_VALUE_TYPE_OCTAL ; 
 unsigned long simple_strtoul (char const*,char**,int) ; 

u8 tomoyo_parse_ulong(unsigned long *result, char **str)
{
	const char *cp = *str;
	char *ep;
	int base = 10;

	if (*cp == '0') {
		char c = *(cp + 1);

		if (c == 'x' || c == 'X') {
			base = 16;
			cp += 2;
		} else if (c >= '0' && c <= '7') {
			base = 8;
			cp++;
		}
	}
	*result = simple_strtoul(cp, &ep, base);
	if (cp == ep)
		return TOMOYO_VALUE_TYPE_INVALID;
	*str = ep;
	switch (base) {
	case 16:
		return TOMOYO_VALUE_TYPE_HEXADECIMAL;
	case 8:
		return TOMOYO_VALUE_TYPE_OCTAL;
	default:
		return TOMOYO_VALUE_TYPE_DECIMAL;
	}
}