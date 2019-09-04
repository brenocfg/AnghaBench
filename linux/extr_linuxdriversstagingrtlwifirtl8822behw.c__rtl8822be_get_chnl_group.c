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

__attribute__((used)) static bool _rtl8822be_get_chnl_group(u8 chnl, u8 *group)
{
	bool in_24g;

	if (chnl <= 14) {
		in_24g = true;

		if (chnl >= 1 && chnl <= 2)
			*group = 0;
		else if (chnl >= 3 && chnl <= 5)
			*group = 1;
		else if (chnl >= 6 && chnl <= 8)
			*group = 2;
		else if (chnl >= 9 && chnl <= 11)
			*group = 3;
		else if (chnl >= 12 && chnl <= 14)
			*group = 4;
	} else {
		in_24g = false;

		if (chnl >= 36 && chnl <= 42)
			*group = 0;
		else if (chnl >= 44 && chnl <= 48)
			*group = 1;
		else if (chnl >= 50 && chnl <= 58)
			*group = 2;
		else if (chnl >= 60 && chnl <= 64)
			*group = 3;
		else if (chnl >= 100 && chnl <= 106)
			*group = 4;
		else if (chnl >= 108 && chnl <= 114)
			*group = 5;
		else if (chnl >= 116 && chnl <= 122)
			*group = 6;
		else if (chnl >= 124 && chnl <= 130)
			*group = 7;
		else if (chnl >= 132 && chnl <= 138)
			*group = 8;
		else if (chnl >= 140 && chnl <= 144)
			*group = 9;
		else if (chnl >= 149 && chnl <= 155)
			*group = 10;
		else if (chnl >= 157 && chnl <= 161)
			*group = 11;
		else if (chnl >= 165 && chnl <= 171)
			*group = 12;
		else if (chnl >= 173 && chnl <= 177)
			*group = 13;
	}
	return in_24g;
}