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
struct ieee80211_device {TYPE_1__* pHTInfo; } ;
struct cb_desc {int bUseShortGI; } ;
struct TYPE_2__ {int bCurBW40MHz; scalar_t__ bCurShortGI20MHz; scalar_t__ bCurShortGI40MHz; scalar_t__ bForcedShortGI; int /*<<< orphan*/  bEnableHT; int /*<<< orphan*/  bCurrentHTSupport; } ;
typedef  TYPE_1__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */

__attribute__((used)) static void
ieee80211_query_HTCapShortGI(struct ieee80211_device *ieee, struct cb_desc *tcb_desc)
{
	PRT_HIGH_THROUGHPUT		pHTInfo = ieee->pHTInfo;

	tcb_desc->bUseShortGI		= false;

	if(!pHTInfo->bCurrentHTSupport||!pHTInfo->bEnableHT)
		return;

	if(pHTInfo->bForcedShortGI)
	{
		tcb_desc->bUseShortGI = true;
		return;
	}

	if((pHTInfo->bCurBW40MHz==true) && pHTInfo->bCurShortGI40MHz)
		tcb_desc->bUseShortGI = true;
	else if((pHTInfo->bCurBW40MHz==false) && pHTInfo->bCurShortGI20MHz)
		tcb_desc->bUseShortGI = true;
}