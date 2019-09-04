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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_device {TYPE_1__* pHTInfo; } ;
struct TYPE_2__ {scalar_t__ bCurShortGI20MHz; scalar_t__ bCurShortGI40MHz; scalar_t__ bCurBW40MHz; } ;
typedef  TYPE_1__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */
 int /*<<< orphan*/ *** MCS_DATA_RATE ; 

u16 HTMcsToDataRate(struct ieee80211_device *ieee, u8 nMcsRate)
{
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;

	u8	is40MHz = (pHTInfo->bCurBW40MHz) ? 1 : 0;
	u8	isShortGI = (pHTInfo->bCurBW40MHz) ?
						((pHTInfo->bCurShortGI40MHz) ? 1 : 0) :
						((pHTInfo->bCurShortGI20MHz) ? 1 : 0);
	return MCS_DATA_RATE[is40MHz][isShortGI][(nMcsRate & 0x7f)];
}