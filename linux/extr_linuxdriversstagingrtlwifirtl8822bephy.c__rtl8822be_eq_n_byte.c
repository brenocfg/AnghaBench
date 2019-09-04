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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;

/* Variables and functions */

__attribute__((used)) static bool _rtl8822be_eq_n_byte(u8 *str1, u8 *str2, u32 num)
{
	if (num == 0)
		return false;
	while (num > 0) {
		num--;
		if (str1[num] != str2[num])
			return false;
	}
	return true;
}