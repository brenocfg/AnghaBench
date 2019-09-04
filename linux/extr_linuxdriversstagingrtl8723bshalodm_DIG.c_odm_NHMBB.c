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
typedef  scalar_t__ u64 ;
struct TYPE_3__ {scalar_t__ NHMCurTxOkcnt; scalar_t__* pNumTxBytesUnicast; scalar_t__ NHMLastTxOkcnt; int NHMCurRxOkcnt; int* pNumRxBytesUnicast; int NHMLastRxOkcnt; int NHM_cnt_0; int adaptivity_flag; int tolerance_cnt; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_DIG ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void odm_NHMBB(void *pDM_VOID)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	/* u8 test_status; */
	/* Pfalse_ALARM_STATISTICS pFalseAlmCnt = &(pDM_Odm->FalseAlmCnt); */

	pDM_Odm->NHMCurTxOkcnt =
		*(pDM_Odm->pNumTxBytesUnicast)-pDM_Odm->NHMLastTxOkcnt;
	pDM_Odm->NHMCurRxOkcnt =
		*(pDM_Odm->pNumRxBytesUnicast)-pDM_Odm->NHMLastRxOkcnt;
	pDM_Odm->NHMLastTxOkcnt =
		*(pDM_Odm->pNumTxBytesUnicast);
	pDM_Odm->NHMLastRxOkcnt =
		*(pDM_Odm->pNumRxBytesUnicast);
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_DIG,
		ODM_DBG_LOUD,
		(
			"NHM_cnt_0 =%d, NHMCurTxOkcnt = %llu, NHMCurRxOkcnt = %llu\n",
			pDM_Odm->NHM_cnt_0,
			pDM_Odm->NHMCurTxOkcnt,
			pDM_Odm->NHMCurRxOkcnt
		)
	);


	if ((pDM_Odm->NHMCurTxOkcnt) + 1 > (u64)(pDM_Odm->NHMCurRxOkcnt<<2) + 1) { /* Tx > 4*Rx possible for adaptivity test */
		if (pDM_Odm->NHM_cnt_0 >= 190 || pDM_Odm->adaptivity_flag == true) {
			/* Enable EDCCA since it is possible running Adaptivity testing */
			/* test_status = 1; */
			pDM_Odm->adaptivity_flag = true;
			pDM_Odm->tolerance_cnt = 0;
		} else {
			if (pDM_Odm->tolerance_cnt < 3)
				pDM_Odm->tolerance_cnt = pDM_Odm->tolerance_cnt + 1;
			else
				pDM_Odm->tolerance_cnt = 4;
			/* test_status = 5; */
			if (pDM_Odm->tolerance_cnt > 3) {
				/* test_status = 3; */
				pDM_Odm->adaptivity_flag = false;
			}
		}
	} else { /*  TX<RX */
		if (pDM_Odm->adaptivity_flag == true && pDM_Odm->NHM_cnt_0 <= 200) {
			/* test_status = 2; */
			pDM_Odm->tolerance_cnt = 0;
		} else {
			if (pDM_Odm->tolerance_cnt < 3)
				pDM_Odm->tolerance_cnt = pDM_Odm->tolerance_cnt + 1;
			else
				pDM_Odm->tolerance_cnt = 4;
			/* test_status = 5; */
			if (pDM_Odm->tolerance_cnt > 3) {
				/* test_status = 4; */
				pDM_Odm->adaptivity_flag = false;
			}
		}
	}

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("adaptivity_flag = %d\n ", pDM_Odm->adaptivity_flag));
}