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
struct iwl_mvm_sta {int /*<<< orphan*/ * ptk_pn; } ;
struct iwl_mvm_key_pn {TYPE_2__* q; } ;
struct iwl_mvm {TYPE_1__* trans; int /*<<< orphan*/  mutex; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  pn; } ;
struct ieee80211_key_seq {TYPE_3__ ccmp; } ;
struct ieee80211_key_conf {size_t keyidx; } ;
struct aes_sc {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pn; } ;
struct TYPE_4__ {int num_rx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  IEEE80211_CCMP_PN_LEN ; 
 int IEEE80211_NUM_TIDS ; 
 int IWL_MAX_TID_COUNT ; 
 int IWL_NUM_RSC ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_set_key_rx_seq (struct ieee80211_key_conf*,int,struct ieee80211_key_seq*) ; 
 int /*<<< orphan*/  iwl_mvm_aes_sc_to_seq (struct aes_sc*,struct ieee80211_key_seq*) ; 
 scalar_t__ iwl_mvm_has_new_rx_api (struct iwl_mvm*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_key_pn* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_set_aes_rx_seq(struct iwl_mvm *mvm, struct aes_sc *scs,
				   struct ieee80211_sta *sta,
				   struct ieee80211_key_conf *key)
{
	int tid;

	BUILD_BUG_ON(IWL_NUM_RSC != IEEE80211_NUM_TIDS);

	if (sta && iwl_mvm_has_new_rx_api(mvm)) {
		struct iwl_mvm_sta *mvmsta;
		struct iwl_mvm_key_pn *ptk_pn;

		mvmsta = iwl_mvm_sta_from_mac80211(sta);

		ptk_pn = rcu_dereference_protected(mvmsta->ptk_pn[key->keyidx],
						   lockdep_is_held(&mvm->mutex));
		if (WARN_ON(!ptk_pn))
			return;

		for (tid = 0; tid < IWL_MAX_TID_COUNT; tid++) {
			struct ieee80211_key_seq seq = {};
			int i;

			iwl_mvm_aes_sc_to_seq(&scs[tid], &seq);
			ieee80211_set_key_rx_seq(key, tid, &seq);
			for (i = 1; i < mvm->trans->num_rx_queues; i++)
				memcpy(ptk_pn->q[i].pn[tid],
				       seq.ccmp.pn, IEEE80211_CCMP_PN_LEN);
		}
	} else {
		for (tid = 0; tid < IWL_NUM_RSC; tid++) {
			struct ieee80211_key_seq seq = {};

			iwl_mvm_aes_sc_to_seq(&scs[tid], &seq);
			ieee80211_set_key_rx_seq(key, tid, &seq);
		}
	}
}