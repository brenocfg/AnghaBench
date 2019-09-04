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
struct odm_ra_info {scalar_t__ PreRate; scalar_t__ LowestRate; scalar_t__ HighestRate; int RAUseRate; int RAWaitingCounter; int RAPendingCounter; int /*<<< orphan*/  RateSGI; scalar_t__ DecisionRate; } ;
struct odm_dm_struct {int dummy; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int /*<<< orphan*/  ODM_COMP_RATE_ADAPTIVE ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_DBG_TRACE ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  odm_SetTxRPTTiming_8188E (struct odm_dm_struct*,struct odm_ra_info*,int) ; 

__attribute__((used)) static int odm_RateDown_8188E(struct odm_dm_struct *dm_odm,
				struct odm_ra_info *pRaInfo)
{
	u8 RateID, LowestRate, HighestRate;
	u8 i;

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE,
			ODM_DBG_TRACE, ("=====>odm_RateDown_8188E()\n"));
	if (!pRaInfo) {
		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
				("odm_RateDown_8188E(): pRaInfo is NULL\n"));
		return -1;
	}
	RateID = pRaInfo->PreRate;
	LowestRate = pRaInfo->LowestRate;
	HighestRate = pRaInfo->HighestRate;

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
		     (" RateID =%d LowestRate =%d HighestRate =%d RateSGI =%d\n",
		     RateID, LowestRate, HighestRate, pRaInfo->RateSGI));
	if (RateID > HighestRate) {
		RateID = HighestRate;
	} else if (pRaInfo->RateSGI) {
		pRaInfo->RateSGI = 0;
	} else if (RateID > LowestRate) {
		if (RateID > 0) {
			for (i = RateID-1; i > LowestRate; i--) {
				if (pRaInfo->RAUseRate & BIT(i)) {
					RateID = i;
					goto RateDownFinish;
				}
			}
		}
	} else if (RateID <= LowestRate) {
		RateID = LowestRate;
	}
RateDownFinish:
	if (pRaInfo->RAWaitingCounter == 1) {
		pRaInfo->RAWaitingCounter += 1;
		pRaInfo->RAPendingCounter += 1;
	} else if (pRaInfo->RAWaitingCounter == 0) {
		;
	} else {
		pRaInfo->RAWaitingCounter = 0;
		pRaInfo->RAPendingCounter = 0;
	}

	if (pRaInfo->RAPendingCounter >= 4)
		pRaInfo->RAPendingCounter = 4;

	pRaInfo->DecisionRate = RateID;
	odm_SetTxRPTTiming_8188E(dm_odm, pRaInfo, 2);
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE,
			ODM_DBG_LOUD, ("Rate down, RPT Timing default\n"));
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
			("RAWaitingCounter %d, RAPendingCounter %d",
			 pRaInfo->RAWaitingCounter, pRaInfo->RAPendingCounter));
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
			("Rate down to RateID %d RateSGI %d\n", RateID, pRaInfo->RateSGI));
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
			("<===== odm_RateDown_8188E()\n"));
	return 0;
}