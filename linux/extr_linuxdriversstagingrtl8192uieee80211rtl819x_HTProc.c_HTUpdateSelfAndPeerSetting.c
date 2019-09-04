#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ bdHTInfoLen; int /*<<< orphan*/  bdHTInfoBuf; } ;
struct ieee80211_network {TYPE_1__ bssht; } ;
struct ieee80211_device {TYPE_2__* pHTInfo; } ;
struct TYPE_6__ {int /*<<< orphan*/  OptMode; } ;
struct TYPE_5__ {int /*<<< orphan*/  CurrentOpMode; scalar_t__ bCurrentHTSupport; } ;
typedef  TYPE_2__* PRT_HIGH_THROUGHPUT ;
typedef  TYPE_3__* PHT_INFORMATION_ELE ;

/* Variables and functions */

void HTUpdateSelfAndPeerSetting(struct ieee80211_device *ieee,	struct ieee80211_network *pNetwork)
{
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
//	PHT_CAPABILITY_ELE		pPeerHTCap = (PHT_CAPABILITY_ELE)pNetwork->bssht.bdHTCapBuf;
	PHT_INFORMATION_ELE		pPeerHTInfo = (PHT_INFORMATION_ELE)pNetwork->bssht.bdHTInfoBuf;

	if (pHTInfo->bCurrentHTSupport) {
		/*
		 * Config current operation mode.
		 */
		if (pNetwork->bssht.bdHTInfoLen != 0)
			pHTInfo->CurrentOpMode = pPeerHTInfo->OptMode;

		/*
		 * <TODO: Config according to OBSS non-HT STA present!!>
		 */
	}
}