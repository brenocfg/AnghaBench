#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_device {scalar_t__ bTxUseDriverAssingedRate; scalar_t__ bTxDisableRateFallBack; TYPE_1__* pHTInfo; } ;
struct TYPE_2__ {int bRegShortGI20MHz; int bRegShortGI40MHz; int bRegBW40MHz; int bRegSuppCCK; unsigned long nAMSDU_MaxSize; int bAMPDUEnable; int AMPDU_Factor; int SelfMimoPs; int bRegRT2RTAggregation; int bRegRxReorderEnable; int RxReorderWinSize; int RxReorderPendingTime; scalar_t__ MPDU_Density; scalar_t__ bAMSDU_Support; } ;
typedef  TYPE_1__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */

void HTUpdateDefaultSetting(struct ieee80211_device *ieee)
{
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	//const typeof( ((struct ieee80211_device *)0)->pHTInfo ) *__mptr = &pHTInfo;

	//printk("pHTinfo:%p, &pHTinfo:%p, mptr:%p,  offsetof:%x\n", pHTInfo, &pHTInfo, __mptr, offsetof(struct ieee80211_device, pHTInfo));
	//printk("===>ieee:%p,\n", ieee);
	// ShortGI support
	pHTInfo->bRegShortGI20MHz = 1;
	pHTInfo->bRegShortGI40MHz = 1;

	// 40MHz channel support
	pHTInfo->bRegBW40MHz = 1;

	// CCK rate support in 40MHz channel
	if (pHTInfo->bRegBW40MHz)
		pHTInfo->bRegSuppCCK = 1;
	else
		pHTInfo->bRegSuppCCK = true;

	// AMSDU related
	pHTInfo->nAMSDU_MaxSize = 7935UL;
	pHTInfo->bAMSDU_Support = 0;

	// AMPDU related
	pHTInfo->bAMPDUEnable = 1;
	pHTInfo->AMPDU_Factor = 2; //// 0: 2n13(8K), 1:2n14(16K), 2:2n15(32K), 3:2n16(64k)
	pHTInfo->MPDU_Density = 0;// 0: No restriction, 1: 1/8usec, 2: 1/4usec, 3: 1/2usec, 4: 1usec, 5: 2usec, 6: 4usec, 7:8usec

	// MIMO Power Save
	pHTInfo->SelfMimoPs = 3;// 0: Static Mimo Ps, 1: Dynamic Mimo Ps, 3: No Limitation, 2: Reserved(Set to 3 automatically.)
	if (pHTInfo->SelfMimoPs == 2)
		pHTInfo->SelfMimoPs = 3;
	// 8190 only. Assign rate operation mode to firmware
	ieee->bTxDisableRateFallBack = 0;
	ieee->bTxUseDriverAssingedRate = 0;

#ifdef	TO_DO_LIST
	// 8190 only. Assign duration operation mode to firmware
	pMgntInfo->bTxEnableFwCalcDur = (BOOLEAN)pNdisCommon->bRegTxEnableFwCalcDur;
#endif
	/*
	 * 8190 only, Realtek proprietary aggregation mode
	 * Set MPDUDensity=2,   1: Set MPDUDensity=2(32k)  for Realtek AP and set MPDUDensity=0(8k) for others
	 */
	pHTInfo->bRegRT2RTAggregation = 1;//0: Set MPDUDensity=2,   1: Set MPDUDensity=2(32k)  for Realtek AP and set MPDUDensity=0(8k) for others

	// For Rx Reorder Control
	pHTInfo->bRegRxReorderEnable = 1;
	pHTInfo->RxReorderWinSize = 64;
	pHTInfo->RxReorderPendingTime = 30;

#ifdef USB_TX_DRIVER_AGGREGATION_ENABLE
	pHTInfo->UsbTxAggrNum = 4;
#endif
#ifdef USB_RX_AGGREGATION_SUPPORT
	pHTInfo->UsbRxFwAggrEn = 1;
	pHTInfo->UsbRxFwAggrPageNum = 24;
	pHTInfo->UsbRxFwAggrPacketNum = 8;
	pHTInfo->UsbRxFwAggrTimeout = 16; ////usb rx FW aggregation timeout threshold.It's in units of 64us
#endif
}