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
struct tkip_sc {int dummy; } ;
struct ieee80211_key_seq {int dummy; } ;
struct ieee80211_key_conf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int IEEE80211_NUM_TIDS ; 
 int IWL_NUM_RSC ; 
 int /*<<< orphan*/  ieee80211_set_key_rx_seq (struct ieee80211_key_conf*,int,struct ieee80211_key_seq*) ; 
 int /*<<< orphan*/  iwl_mvm_tkip_sc_to_seq (struct tkip_sc*,struct ieee80211_key_seq*) ; 

__attribute__((used)) static void iwl_mvm_set_tkip_rx_seq(struct tkip_sc *scs,
				    struct ieee80211_key_conf *key)
{
	int tid;

	BUILD_BUG_ON(IWL_NUM_RSC != IEEE80211_NUM_TIDS);

	for (tid = 0; tid < IWL_NUM_RSC; tid++) {
		struct ieee80211_key_seq seq = {};

		iwl_mvm_tkip_sc_to_seq(&scs[tid], &seq);
		ieee80211_set_key_rx_seq(key, tid, &seq);
	}
}