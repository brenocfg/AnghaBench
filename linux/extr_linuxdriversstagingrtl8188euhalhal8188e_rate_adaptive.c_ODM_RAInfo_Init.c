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
struct odm_ra_info {size_t DecisionRate; size_t PreRate; size_t HighestRate; int RateMask; int RAUseRate; int NscDown; int NscUp; int Active; int RptTime; int PTActive; int PTStage; int PTSmoothFactor; scalar_t__ RAstage; scalar_t__ PTModeSS; scalar_t__ PTPreRssi; scalar_t__ PTPreRate; scalar_t__ PTStopCount; scalar_t__ PTTryState; scalar_t__ RAPendingCounter; scalar_t__ RAWaitingCounter; scalar_t__ TOTAL; scalar_t__* RTY; scalar_t__ DROP; scalar_t__ RateSGI; scalar_t__ SGIEnable; scalar_t__ PreRssiStaRA; scalar_t__ RssiStaRA; scalar_t__ RateID; scalar_t__ LowestRate; } ;
struct odm_dm_struct {size_t* pWirelessMode; struct odm_ra_info* RAInfo; } ;

/* Variables and functions */
 int* N_THRESHOLD_HIGH ; 
 int* N_THRESHOLD_LOW ; 
 int /*<<< orphan*/  ODM_COMP_RATE_ADAPTIVE ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 size_t ODM_WM_B ; 
 size_t ODM_WM_G ; 
 size_t ODM_WM_N24G ; 

int ODM_RAInfo_Init(struct odm_dm_struct *dm_odm, u8 macid)
{
	struct odm_ra_info *pRaInfo = &dm_odm->RAInfo[macid];
	u8 WirelessMode = 0xFF; /* invalid value */
	u8 max_rate_idx = 0x13; /* MCS7 */

	if (dm_odm->pWirelessMode)
		WirelessMode = *(dm_odm->pWirelessMode);

	if (WirelessMode != 0xFF) {
		if (WirelessMode & ODM_WM_N24G)
			max_rate_idx = 0x13;
		else if (WirelessMode & ODM_WM_G)
			max_rate_idx = 0x0b;
		else if (WirelessMode & ODM_WM_B)
			max_rate_idx = 0x03;
	}

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD,
		     ("ODM_RAInfo_Init(): WirelessMode:0x%08x , max_raid_idx:0x%02x\n",
		     WirelessMode, max_rate_idx));

	pRaInfo->DecisionRate = max_rate_idx;
	pRaInfo->PreRate = max_rate_idx;
	pRaInfo->HighestRate = max_rate_idx;
	pRaInfo->LowestRate = 0;
	pRaInfo->RateID = 0;
	pRaInfo->RateMask = 0xffffffff;
	pRaInfo->RssiStaRA = 0;
	pRaInfo->PreRssiStaRA = 0;
	pRaInfo->SGIEnable = 0;
	pRaInfo->RAUseRate = 0xffffffff;
	pRaInfo->NscDown = (N_THRESHOLD_HIGH[0x13]+N_THRESHOLD_LOW[0x13])/2;
	pRaInfo->NscUp = (N_THRESHOLD_HIGH[0x13]+N_THRESHOLD_LOW[0x13])/2;
	pRaInfo->RateSGI = 0;
	pRaInfo->Active = 1;	/* Active is not used at present. by page, 110819 */
	pRaInfo->RptTime = 0x927c;
	pRaInfo->DROP = 0;
	pRaInfo->RTY[0] = 0;
	pRaInfo->RTY[1] = 0;
	pRaInfo->RTY[2] = 0;
	pRaInfo->RTY[3] = 0;
	pRaInfo->RTY[4] = 0;
	pRaInfo->TOTAL = 0;
	pRaInfo->RAWaitingCounter = 0;
	pRaInfo->RAPendingCounter = 0;
	pRaInfo->PTActive = 1;   /*  Active when this STA is use */
	pRaInfo->PTTryState = 0;
	pRaInfo->PTStage = 5; /*  Need to fill into HW_PWR_STATUS */
	pRaInfo->PTSmoothFactor = 192;
	pRaInfo->PTStopCount = 0;
	pRaInfo->PTPreRate = 0;
	pRaInfo->PTPreRssi = 0;
	pRaInfo->PTModeSS = 0;
	pRaInfo->RAstage = 0;
	return 0;
}