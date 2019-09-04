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

__attribute__((used)) static u8 Hal_GetChnlGroup88E(u8 chnl, u8 *pGroup)
{
	u8 bIn24G = true;

	if (chnl <= 14) {
		bIn24G = true;

		if (chnl < 3)			/*  Channel 1-2 */
			*pGroup = 0;
		else if (chnl < 6)		/*  Channel 3-5 */
			*pGroup = 1;
		else	 if (chnl < 9)		/*  Channel 6-8 */
			*pGroup = 2;
		else if (chnl < 12)		/*  Channel 9-11 */
			*pGroup = 3;
		else if (chnl < 14)		/*  Channel 12-13 */
			*pGroup = 4;
		else if (chnl == 14)		/*  Channel 14 */
			*pGroup = 5;
	} else {
		/* probably, this branch is suitable only for 5 GHz */

		bIn24G = false;

		if (chnl <= 40)
			*pGroup = 0;
		else if (chnl <= 48)
			*pGroup = 1;
		else	 if (chnl <= 56)
			*pGroup = 2;
		else if (chnl <= 64)
			*pGroup = 3;
		else if (chnl <= 104)
			*pGroup = 4;
		else if (chnl <= 112)
			*pGroup = 5;
		else if (chnl <= 120)
			*pGroup = 5;
		else if (chnl <= 128)
			*pGroup = 6;
		else if (chnl <= 136)
			*pGroup = 7;
		else if (chnl <= 144)
			*pGroup = 8;
		else if (chnl <= 153)
			*pGroup = 9;
		else if (chnl <= 161)
			*pGroup = 10;
		else if (chnl <= 177)
			*pGroup = 11;
	}
	return bIn24G;
}