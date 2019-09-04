#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_4__ {int /*<<< orphan*/ * pkts; } ;
struct iwl_mvm_tcm_mac {TYPE_2__ tx; } ;
struct iwl_mvm_sta {int mac_id_n_color; } ;
struct TYPE_3__ {struct iwl_mvm_tcm_mac* data; } ;
struct iwl_mvm {TYPE_1__ tcm; } ;

/* Variables and functions */
 int FW_CTXT_ID_MSK ; 
 size_t* tid_to_mac80211_ac ; 

__attribute__((used)) static void iwl_mvm_tx_pkt_queued(struct iwl_mvm *mvm,
				  struct iwl_mvm_sta *mvmsta, int tid)
{
	u32 ac = tid_to_mac80211_ac[tid];
	int mac = mvmsta->mac_id_n_color & FW_CTXT_ID_MSK;
	struct iwl_mvm_tcm_mac *mdata = &mvm->tcm.data[mac];

	mdata->tx.pkts[ac]++;
}