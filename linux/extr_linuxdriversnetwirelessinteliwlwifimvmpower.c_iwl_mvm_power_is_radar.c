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
struct ieee80211_vif {int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_channel {int flags; } ;
struct TYPE_2__ {struct ieee80211_channel* chan; } ;
struct ieee80211_chanctx_conf {TYPE_1__ def; } ;

/* Variables and functions */
 int IEEE80211_CHAN_RADAR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static bool iwl_mvm_power_is_radar(struct ieee80211_vif *vif)
{
	struct ieee80211_chanctx_conf *chanctx_conf;
	struct ieee80211_channel *chan;
	bool radar_detect = false;

	rcu_read_lock();
	chanctx_conf = rcu_dereference(vif->chanctx_conf);
	WARN_ON(!chanctx_conf);
	if (chanctx_conf) {
		chan = chanctx_conf->def.chan;
		radar_detect = chan->flags & IEEE80211_CHAN_RADAR;
	}
	rcu_read_unlock();

	return radar_detect;
}