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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct tid_ampdu_tx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tid_tx; } ;
struct sta_info {TYPE_1__ ampdu_mlme; } ;
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 size_t IEEE80211_NUM_TIDS ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ht_dbg (struct ieee80211_sub_if_data*,char*,...) ; 
 struct tid_ampdu_tx* rcu_dereference (int /*<<< orphan*/ ) ; 
 struct sta_info* sta_info_get_bss (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static struct tid_ampdu_tx *
ieee80211_lookup_tid_tx(struct ieee80211_sub_if_data *sdata,
			const u8 *ra, u16 tid, struct sta_info **sta)
{
	struct tid_ampdu_tx *tid_tx;

	if (tid >= IEEE80211_NUM_TIDS) {
		ht_dbg(sdata, "Bad TID value: tid = %d (>= %d)\n",
		       tid, IEEE80211_NUM_TIDS);
		return NULL;
	}

	*sta = sta_info_get_bss(sdata, ra);
	if (!*sta) {
		ht_dbg(sdata, "Could not find station: %pM\n", ra);
		return NULL;
	}

	tid_tx = rcu_dereference((*sta)->ampdu_mlme.tid_tx[tid]);

	if (WARN_ON(!tid_tx))
		ht_dbg(sdata, "addBA was not requested!\n");

	return tid_tx;
}