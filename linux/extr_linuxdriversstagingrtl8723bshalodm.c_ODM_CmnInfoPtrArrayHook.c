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
typedef  size_t u16 ;
struct TYPE_3__ {int /*<<< orphan*/ * pODM_StaInfo; } ;
typedef  int /*<<< orphan*/  PSTA_INFO_T ;
typedef  TYPE_1__* PDM_ODM_T ;
typedef  int ODM_CMNINFO_E ;

/* Variables and functions */
#define  ODM_CMNINFO_STA_STATUS 128 

void ODM_CmnInfoPtrArrayHook(
	PDM_ODM_T pDM_Odm,
	ODM_CMNINFO_E CmnInfo,
	u16 Index,
	void *pValue
)
{
	/*  */
	/*  Hook call by reference pointer. */
	/*  */
	switch (CmnInfo) {
	/*  */
	/*  Dynamic call by reference pointer. */
	/*  */
	case ODM_CMNINFO_STA_STATUS:
		pDM_Odm->pODM_StaInfo[Index] = (PSTA_INFO_T)pValue;
		break;
	/* To remove the compiler warning, must add an empty default statement to handle the other values. */
	default:
		/* do nothing */
		break;
	}

}