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
typedef  int u8 ;
struct ieee80211_device {int basic_rate; scalar_t__ mode; TYPE_1__* pHTInfo; } ;
struct TYPE_2__ {int IOTAction; int /*<<< orphan*/  bCurSuppCCK; } ;
typedef  TYPE_1__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */
 int HT_IOT_ACT_MGNT_USE_CCK_6M ; 
 scalar_t__ IEEE_A ; 
 scalar_t__ IEEE_N_24G ; 
 scalar_t__ IEEE_N_5G ; 

__attribute__((used)) static u8 MgntQuery_MgntFrameTxRate(struct ieee80211_device *ieee)
{
	PRT_HIGH_THROUGHPUT      pHTInfo = ieee->pHTInfo;
	u8 rate;

	/* 2008/01/25 MH For broadcom, MGNT frame set as OFDM 6M. */
	if (pHTInfo->IOTAction & HT_IOT_ACT_MGNT_USE_CCK_6M)
		rate = 0x0c;
	else
		rate = ieee->basic_rate & 0x7f;

	if (rate == 0) {
		/* 2005.01.26, by rcnjko. */
		if (ieee->mode == IEEE_A ||
		    ieee->mode == IEEE_N_5G ||
		    (ieee->mode == IEEE_N_24G && !pHTInfo->bCurSuppCCK))
			rate = 0x0c;
		else
			rate = 0x02;
	}

	/*
	// Data rate of ProbeReq is already decided. Annie, 2005-03-31
	if( pMgntInfo->bScanInProgress || (pMgntInfo->bDualModeScanStep!=0) ) {
	if(pMgntInfo->dot11CurrentWirelessMode==WIRELESS_MODE_A)
	rate = 0x0c;
	else
	rate = 0x02;
	}
	 */
	return rate;
}