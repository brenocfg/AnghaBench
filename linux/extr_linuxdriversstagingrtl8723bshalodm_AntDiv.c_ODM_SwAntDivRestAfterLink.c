#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  TYPE_1__* pSWAT_T ;
typedef  TYPE_2__* pFAT_T ;
struct TYPE_6__ {scalar_t__* AuxAnt_Cnt; scalar_t__* MainAnt_Cnt; scalar_t__* AuxAnt_Sum; scalar_t__* MainAnt_Sum; int /*<<< orphan*/  RxIdleAnt; } ;
struct TYPE_5__ {int try_flag; scalar_t__ Double_chk_flag; scalar_t__ RSSI_Trying; } ;
struct TYPE_7__ {int RSSI_test; TYPE_2__ DM_FatTable; TYPE_1__ DM_SWAT_Table; } ;
typedef  TYPE_3__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  MAIN_ANT ; 
 size_t ODM_ASSOCIATE_ENTRY_NUM ; 

void ODM_SwAntDivRestAfterLink(PDM_ODM_T pDM_Odm)
{
	pSWAT_T pDM_SWAT_Table = &pDM_Odm->DM_SWAT_Table;
	pFAT_T pDM_FatTable = &pDM_Odm->DM_FatTable;
	u32 i;

	pDM_Odm->RSSI_test = false;
	pDM_SWAT_Table->try_flag = 0xff;
	pDM_SWAT_Table->RSSI_Trying = 0;
	pDM_SWAT_Table->Double_chk_flag = 0;

	pDM_FatTable->RxIdleAnt = MAIN_ANT;

	for (i = 0; i < ODM_ASSOCIATE_ENTRY_NUM; i++) {
		pDM_FatTable->MainAnt_Sum[i] = 0;
		pDM_FatTable->AuxAnt_Sum[i] = 0;
		pDM_FatTable->MainAnt_Cnt[i] = 0;
		pDM_FatTable->AuxAnt_Cnt[i] = 0;
	}
}