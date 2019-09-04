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
typedef  size_t u8 ;
struct sta_info {int dummy; } ;
struct odm_dm_struct {scalar_t__* pBandWidth; int* pSecChOffset; int bOneEntryOnly; struct sta_info** pODM_StaInfo; scalar_t__* pChannel; scalar_t__ ControlChannel; } ;

/* Variables and functions */
 scalar_t__ IS_STA_VALID (struct sta_info*) ; 
 size_t ODM_ASSOCIATE_ENTRY_NUM ; 
 scalar_t__ ODM_BW40M ; 

void odm_CommonInfoSelfUpdate(struct odm_dm_struct *pDM_Odm)
{
	u8 EntryCnt = 0;
	u8 i;
	struct sta_info *pEntry;

	if (*(pDM_Odm->pBandWidth) == ODM_BW40M) {
		if (*(pDM_Odm->pSecChOffset) == 1)
			pDM_Odm->ControlChannel = *(pDM_Odm->pChannel) - 2;
		else if (*(pDM_Odm->pSecChOffset) == 2)
			pDM_Odm->ControlChannel = *(pDM_Odm->pChannel) + 2;
	} else {
		pDM_Odm->ControlChannel = *(pDM_Odm->pChannel);
	}

	for (i = 0; i < ODM_ASSOCIATE_ENTRY_NUM; i++) {
		pEntry = pDM_Odm->pODM_StaInfo[i];
		if (IS_STA_VALID(pEntry))
			EntryCnt++;
	}
	if (EntryCnt == 1)
		pDM_Odm->bOneEntryOnly = true;
	else
		pDM_Odm->bOneEntryOnly = false;
}