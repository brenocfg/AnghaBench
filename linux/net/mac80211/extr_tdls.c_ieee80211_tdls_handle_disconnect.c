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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  vif; } ;
struct ieee80211_sta {int /*<<< orphan*/  tdls; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NL80211_TDLS_TEARDOWN ; 
 int /*<<< orphan*/  WLAN_REASON_TDLS_TEARDOWN_UNREACHABLE ; 
 struct ieee80211_sta* ieee80211_find_sta (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ieee80211_get_reason_code_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tdls_oper_request (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  tdls_dbg (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ieee80211_tdls_handle_disconnect(struct ieee80211_sub_if_data *sdata,
				      const u8 *peer, u16 reason)
{
	struct ieee80211_sta *sta;

	rcu_read_lock();
	sta = ieee80211_find_sta(&sdata->vif, peer);
	if (!sta || !sta->tdls) {
		rcu_read_unlock();
		return;
	}
	rcu_read_unlock();

	tdls_dbg(sdata, "disconnected from TDLS peer %pM (Reason: %u=%s)\n",
		 peer, reason,
		 ieee80211_get_reason_code_string(reason));

	ieee80211_tdls_oper_request(&sdata->vif, peer,
				    NL80211_TDLS_TEARDOWN,
				    WLAN_REASON_TDLS_TEARDOWN_UNREACHABLE,
				    GFP_ATOMIC);
}