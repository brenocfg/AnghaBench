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
typedef  size_t u16 ;

/* Variables and functions */

__attribute__((used)) static bool _rtl8812ae_get_integer_from_string(char *str, u8 *pint)
{
	u16 i = 0;
	*pint = 0;

	while (str[i] != '\0') {
		if (str[i] >= '0' && str[i] <= '9') {
			*pint *= 10;
			*pint += (str[i] - '0');
		} else {
			return false;
		}
		++i;
	}

	return true;
}