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
struct odm_ra_info {scalar_t__ PreRate; scalar_t__ HighestRate; int RAWaitingCounter; size_t RAPendingCounter; int RAUseRate; int SGIEnable; int RateSGI; scalar_t__ DecisionRate; int /*<<< orphan*/  RssiStaRA; int /*<<< orphan*/  PreRssiStaRA; } ;
struct odm_dm_struct {int dummy; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int /*<<< orphan*/  ODM_COMP_RATE_ADAPTIVE ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_DBG_TRACE ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int* PendingForRateUpFail ; 
 int /*<<< orphan*/  odm_SetTxRPTTiming_8188E (struct odm_dm_struct*,struct odm_ra_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int odm_RateUp_8188E(
		struct odm_dm_struct *dm_odm,
		struct odm_ra_info *pRaInfo
	)
{
	u8 RateID, HighestRate;
	u8 i;

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE,
			ODM_DBG_TRACE, ("=====>odm_RateUp_8188E()\n"));
	if (!pRaInfo) {
		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
				("odm_RateUp_8188E(): pRaInfo is NULL\n"));
		return -1;
	}
	RateID = pRaInfo->PreRate;
	HighestRate = pRaInfo->HighestRate;
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
		     (" RateID =%d HighestRate =%d\n",
		     RateID, HighestRate));
	if (pRaInfo->RAWaitingCounter == 1) {
		pRaInfo->RAWaitingCounter = 0;
		pRaInfo->RAPendingCounter = 0;
	} else if (pRaInfo->RAWaitingCounter > 1) {
		pRaInfo->PreRssiStaRA = pRaInfo->RssiStaRA;
		goto RateUpfinish;
	}
	odm_SetTxRPTTiming_8188E(dm_odm, pRaInfo, 0);
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
			("odm_RateUp_8188E():Decrease RPT Timing\n"));

	if (RateID < HighestRate) {
		for (i = RateID+1; i <= HighestRate; i++) {
			if (pRaInfo->RAUseRate & BIT(i)) {
				RateID = i;
				goto RateUpfinish;
			}
		}
	} else if (RateID == HighestRate) {
		if (pRaInfo->SGIEnable && (pRaInfo->RateSGI != 1))
			pRaInfo->RateSGI = 1;
		else if ((pRaInfo->SGIEnable) != 1)
			pRaInfo->RateSGI = 0;
	} else {
		RateID = HighestRate;
	}
RateUpfinish:
	if (pRaInfo->RAWaitingCounter ==
		(4+PendingForRateUpFail[pRaInfo->RAPendingCounter]))
		pRaInfo->RAWaitingCounter = 0;
	else
		pRaInfo->RAWaitingCounter++;

	pRaInfo->DecisionRate = RateID;
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
			("Rate up to RateID %d\n", RateID));
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
			("RAWaitingCounter %d, RAPendingCounter %d",
			 pRaInfo->RAWaitingCounter, pRaInfo->RAPendingCounter));
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE,
			ODM_DBG_TRACE, ("<===== odm_RateUp_8188E()\n"));
	return 0;
}