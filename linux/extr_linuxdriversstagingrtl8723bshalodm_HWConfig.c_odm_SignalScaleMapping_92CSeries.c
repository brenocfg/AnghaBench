#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int s32 ;
struct TYPE_3__ {scalar_t__ SupportInterface; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 scalar_t__ ODM_ITRF_SDIO ; 

__attribute__((used)) static s32 odm_SignalScaleMapping_92CSeries(PDM_ODM_T pDM_Odm, s32 CurrSig)
{
	s32 RetSig = 0;

	if (pDM_Odm->SupportInterface  == ODM_ITRF_SDIO) {
		if (CurrSig >= 51 && CurrSig <= 100)
			RetSig = 100;
		else if (CurrSig >= 41 && CurrSig <= 50)
			RetSig = 80 + ((CurrSig - 40)*2);
		else if (CurrSig >= 31 && CurrSig <= 40)
			RetSig = 66 + (CurrSig - 30);
		else if (CurrSig >= 21 && CurrSig <= 30)
			RetSig = 54 + (CurrSig - 20);
		else if (CurrSig >= 10 && CurrSig <= 20)
			RetSig = 42 + (((CurrSig - 10) * 2) / 3);
		else if (CurrSig >= 5 && CurrSig <= 9)
			RetSig = 22 + (((CurrSig - 5) * 3) / 2);
		else if (CurrSig >= 1 && CurrSig <= 4)
			RetSig = 6 + (((CurrSig - 1) * 3) / 2);
		else
			RetSig = CurrSig;
	}

	return RetSig;
}