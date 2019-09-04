#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_12__ {int /*<<< orphan*/  uc_tsid; } ;
struct TYPE_13__ {TYPE_1__ ts_info; } ;
struct TYPE_18__ {int /*<<< orphan*/  addr; TYPE_2__ t_spec; } ;
struct TYPE_16__ {int SeqNum; } ;
struct TYPE_17__ {TYPE_5__ field; } ;
struct TYPE_14__ {int BufferSize; int /*<<< orphan*/  TID; int /*<<< orphan*/  BAPolicy; scalar_t__ AMSDU_Support; } ;
struct TYPE_15__ {TYPE_3__ field; } ;
struct TYPE_19__ {TYPE_6__ BaStartSeqCtrl; scalar_t__ BaTimeoutValue; TYPE_4__ BaParamSet; int /*<<< orphan*/  DialogToken; scalar_t__ bValid; } ;
struct tx_ts_record {int tx_cur_seq; TYPE_7__ ts_common_info; TYPE_8__ tx_pending_ba_record; } ;
struct ieee80211_device {int dummy; } ;
typedef  TYPE_8__* PBA_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  ActivateBAEntry (struct ieee80211_device*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BA_SETUP_TIMEOUT ; 
 int /*<<< orphan*/  DeActivateBAEntry (struct ieee80211_device*,TYPE_8__*) ; 
 int /*<<< orphan*/  ieee80211_send_ADDBAReq (struct ieee80211_device*,int /*<<< orphan*/ ,TYPE_8__*) ; 

void
TsInitAddBA(
	struct ieee80211_device *ieee,
	struct tx_ts_record     *pTS,
	u8		Policy,
	u8		bOverwritePending
	)
{
	PBA_RECORD			pBA = &pTS->tx_pending_ba_record;

	if (pBA->bValid && !bOverwritePending)
		return;

	// Set parameters to "Pending" variable set
	DeActivateBAEntry(ieee, pBA);

	pBA->DialogToken++;						// DialogToken: Only keep the latest dialog token
	pBA->BaParamSet.field.AMSDU_Support = 0;	// Do not support A-MSDU with A-MPDU now!!
	pBA->BaParamSet.field.BAPolicy = Policy;	// Policy: Delayed or Immediate
	pBA->BaParamSet.field.TID = pTS->ts_common_info.t_spec.ts_info.uc_tsid;	// TID
	// BufferSize: This need to be set according to A-MPDU vector
	pBA->BaParamSet.field.BufferSize = 32;		// BufferSize: This need to be set according to A-MPDU vector
	pBA->BaTimeoutValue = 0;					// Timeout value: Set 0 to disable Timer
	pBA->BaStartSeqCtrl.field.SeqNum = (pTS->tx_cur_seq + 3) % 4096;	// Block Ack will start after 3 packets later.

	ActivateBAEntry(ieee, pBA, BA_SETUP_TIMEOUT);

	ieee80211_send_ADDBAReq(ieee, pTS->ts_common_info.addr, pBA);
}