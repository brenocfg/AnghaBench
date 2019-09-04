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

__attribute__((used)) static u8 _rtl92ee_get_chnl_group(u8 chnl)
{
	u8 group = 0;

	if (chnl <= 14) {
		if (1 <= chnl && chnl <= 2)
			group = 0;
		else if (3 <= chnl && chnl <= 5)
			group = 1;
		else if (6 <= chnl && chnl <= 8)
			group = 2;
		else if (9 <= chnl && chnl <= 11)
			group = 3;
		else if (12 <= chnl && chnl <= 14)
			group = 4;
	} else {
		if (36 <= chnl && chnl <= 42)
			group = 0;
		else if (44 <= chnl && chnl <= 48)
			group = 1;
		else if (50 <= chnl && chnl <= 58)
			group = 2;
		else if (60 <= chnl && chnl <= 64)
			group = 3;
		else if (100 <= chnl && chnl <= 106)
			group = 4;
		else if (108 <= chnl && chnl <= 114)
			group = 5;
		else if (116 <= chnl && chnl <= 122)
			group = 6;
		else if (124 <= chnl && chnl <= 130)
			group = 7;
		else if (132 <= chnl && chnl <= 138)
			group = 8;
		else if (140 <= chnl && chnl <= 144)
			group = 9;
		else if (149 <= chnl && chnl <= 155)
			group = 10;
		else if (157 <= chnl && chnl <= 161)
			group = 11;
		else if (165 <= chnl && chnl <= 171)
			group = 12;
		else if (173 <= chnl && chnl <= 177)
			group = 13;
	}
	return group;
}