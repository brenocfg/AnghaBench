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
struct odm_ra_info {scalar_t__ TOTAL; int RssiStaRA; int PreRssiStaRA; scalar_t__ PreRate; scalar_t__ HighestRate; int NscDown; int* RTY; int NscUp; scalar_t__ DROP; scalar_t__ DecisionRate; int /*<<< orphan*/  RateSGI; scalar_t__ RAPendingCounter; scalar_t__ RAWaitingCounter; scalar_t__ Active; } ;
struct odm_dm_struct {int dummy; } ;

/* Variables and functions */
 scalar_t__* DROPING_NECESSARY ; 
 int* N_THRESHOLD_HIGH ; 
 int* N_THRESHOLD_LOW ; 
 int ODM_COMP_INIT ; 
 int ODM_COMP_RATE_ADAPTIVE ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_DBG_TRACE ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int,int /*<<< orphan*/ ,char*) ; 
 int** RETRY_PENALTY ; 
 size_t** RETRY_PENALTY_IDX ; 
 size_t* RETRY_PENALTY_UP_IDX ; 
 int* RSSI_THRESHOLD ; 
 int /*<<< orphan*/  odm_RateDown_8188E (struct odm_dm_struct*,struct odm_ra_info*) ; 
 int /*<<< orphan*/  odm_RateUp_8188E (struct odm_dm_struct*,struct odm_ra_info*) ; 
 int /*<<< orphan*/  odm_ResetRaCounter_8188E (struct odm_ra_info*) ; 
 int /*<<< orphan*/  odm_SetTxRPTTiming_8188E (struct odm_dm_struct*,struct odm_ra_info*,int) ; 

__attribute__((used)) static void odm_RateDecision_8188E(struct odm_dm_struct *dm_odm,
		struct odm_ra_info *pRaInfo
	)
{
	u8 RateID = 0, RtyPtID = 0, PenaltyID1 = 0, PenaltyID2 = 0, i = 0;
	/* u32 pool_retry; */
	static u8 DynamicTxRPTTimingCounter;

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
			("=====>odm_RateDecision_8188E()\n"));

	if (pRaInfo->Active && (pRaInfo->TOTAL > 0)) { /*  STA used and data packet exits */
		if ((pRaInfo->RssiStaRA < (pRaInfo->PreRssiStaRA - 3)) ||
		    (pRaInfo->RssiStaRA > (pRaInfo->PreRssiStaRA + 3))) {
			pRaInfo->RAWaitingCounter = 0;
			pRaInfo->RAPendingCounter = 0;
		}
		/*  Start RA decision */
		if (pRaInfo->PreRate > pRaInfo->HighestRate)
			RateID = pRaInfo->HighestRate;
		else
			RateID = pRaInfo->PreRate;
		if (pRaInfo->RssiStaRA > RSSI_THRESHOLD[RateID])
			RtyPtID = 0;
		else
			RtyPtID = 1;
		PenaltyID1 = RETRY_PENALTY_IDX[RtyPtID][RateID]; /* TODO by page */

		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
			     (" NscDown init is %d\n", pRaInfo->NscDown));

		for (i = 0 ; i <= 4 ; i++)
			pRaInfo->NscDown += pRaInfo->RTY[i] * RETRY_PENALTY[PenaltyID1][i];

		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
			     (" NscDown is %d, total*penalty[5] is %d\n", pRaInfo->NscDown,
			      (pRaInfo->TOTAL * RETRY_PENALTY[PenaltyID1][5])));

		if (pRaInfo->NscDown > (pRaInfo->TOTAL * RETRY_PENALTY[PenaltyID1][5]))
			pRaInfo->NscDown -= pRaInfo->TOTAL * RETRY_PENALTY[PenaltyID1][5];
		else
			pRaInfo->NscDown = 0;

		/*  rate up */
		PenaltyID2 = RETRY_PENALTY_UP_IDX[RateID];
		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
			     (" NscUp init is %d\n", pRaInfo->NscUp));

		for (i = 0 ; i <= 4 ; i++)
			pRaInfo->NscUp += pRaInfo->RTY[i] * RETRY_PENALTY[PenaltyID2][i];

		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
			     ("NscUp is %d, total*up[5] is %d\n",
			     pRaInfo->NscUp, (pRaInfo->TOTAL * RETRY_PENALTY[PenaltyID2][5])));

		if (pRaInfo->NscUp > (pRaInfo->TOTAL * RETRY_PENALTY[PenaltyID2][5]))
			pRaInfo->NscUp -= pRaInfo->TOTAL * RETRY_PENALTY[PenaltyID2][5];
		else
			pRaInfo->NscUp = 0;

		ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE|ODM_COMP_INIT, ODM_DBG_LOUD,
			     (" RssiStaRa = %d RtyPtID =%d PenaltyID1 = 0x%x  PenaltyID2 = 0x%x RateID =%d NscDown =%d NscUp =%d SGI =%d\n",
			     pRaInfo->RssiStaRA, RtyPtID, PenaltyID1, PenaltyID2, RateID, pRaInfo->NscDown, pRaInfo->NscUp, pRaInfo->RateSGI));
		if ((pRaInfo->NscDown < N_THRESHOLD_LOW[RateID]) ||
		    (pRaInfo->DROP > DROPING_NECESSARY[RateID]))
			odm_RateDown_8188E(dm_odm, pRaInfo);
		else if (pRaInfo->NscUp > N_THRESHOLD_HIGH[RateID])
			odm_RateUp_8188E(dm_odm, pRaInfo);

		if (pRaInfo->DecisionRate > pRaInfo->HighestRate)
			pRaInfo->DecisionRate = pRaInfo->HighestRate;

		if ((pRaInfo->DecisionRate) == (pRaInfo->PreRate))
			DynamicTxRPTTimingCounter += 1;
		else
			DynamicTxRPTTimingCounter = 0;

		if (DynamicTxRPTTimingCounter >= 4) {
			odm_SetTxRPTTiming_8188E(dm_odm, pRaInfo, 1);
			ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE,
				     ODM_DBG_LOUD, ("<===== Rate don't change 4 times, Extend RPT Timing\n"));
			DynamicTxRPTTimingCounter = 0;
		}

		pRaInfo->PreRate = pRaInfo->DecisionRate;  /* YJ, add, 120120 */

		odm_ResetRaCounter_8188E(pRaInfo);
	}
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE, ("<===== odm_RateDecision_8188E()\n"));
}