#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_3__ {scalar_t__ bValid; } ;
struct tx_ts_record {TYPE_1__ tx_pending_ba_record; TYPE_1__ tx_admitted_ba_record; } ;
struct ieee80211_device {int dummy; } ;
typedef  TYPE_1__* PBA_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeActivateBAEntry (struct ieee80211_device*,TYPE_1__*) ; 

__attribute__((used)) static u8 TxTsDeleteBA(struct ieee80211_device *ieee, struct tx_ts_record *pTxTs)
{
	PBA_RECORD		pAdmittedBa = &pTxTs->tx_admitted_ba_record;  //These two BA entries must exist in TS structure
	PBA_RECORD		pPendingBa = &pTxTs->tx_pending_ba_record;
	u8			bSendDELBA = false;

	// Delete pending BA
	if (pPendingBa->bValid) {
		DeActivateBAEntry(ieee, pPendingBa);
		bSendDELBA = true;
	}

	// Delete admitted BA
	if (pAdmittedBa->bValid) {
		DeActivateBAEntry(ieee, pAdmittedBa);
		bSendDELBA = true;
	}

	return bSendDELBA;
}