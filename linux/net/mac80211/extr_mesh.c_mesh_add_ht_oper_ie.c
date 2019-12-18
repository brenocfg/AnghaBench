#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct ieee80211_sta_ht_cap {int /*<<< orphan*/  ht_supported; } ;
struct ieee80211_supported_band {struct ieee80211_sta_ht_cap ht_cap; } ;
struct TYPE_12__ {scalar_t__ width; } ;
struct TYPE_10__ {int /*<<< orphan*/  ht_operation_mode; TYPE_6__ chandef; } ;
struct TYPE_11__ {TYPE_4__ bss_conf; int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_sub_if_data {TYPE_5__ vif; struct ieee80211_local* local; } ;
struct TYPE_9__ {TYPE_2__* wiphy; } ;
struct ieee80211_local {TYPE_3__ hw; } ;
struct ieee80211_ht_operation {int dummy; } ;
struct ieee80211_channel {size_t band; } ;
struct TYPE_7__ {struct ieee80211_channel* chan; } ;
struct ieee80211_chanctx_conf {TYPE_1__ def; } ;
struct TYPE_8__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ NL80211_CHAN_WIDTH_10 ; 
 scalar_t__ NL80211_CHAN_WIDTH_20_NOHT ; 
 scalar_t__ NL80211_CHAN_WIDTH_5 ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_ie_build_ht_oper (int /*<<< orphan*/ *,struct ieee80211_sta_ht_cap*,TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 

int mesh_add_ht_oper_ie(struct ieee80211_sub_if_data *sdata,
			struct sk_buff *skb)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_chanctx_conf *chanctx_conf;
	struct ieee80211_channel *channel;
	struct ieee80211_supported_band *sband;
	struct ieee80211_sta_ht_cap *ht_cap;
	u8 *pos;

	rcu_read_lock();
	chanctx_conf = rcu_dereference(sdata->vif.chanctx_conf);
	if (WARN_ON(!chanctx_conf)) {
		rcu_read_unlock();
		return -EINVAL;
	}
	channel = chanctx_conf->def.chan;
	rcu_read_unlock();

	sband = local->hw.wiphy->bands[channel->band];
	ht_cap = &sband->ht_cap;

	if (!ht_cap->ht_supported ||
	    sdata->vif.bss_conf.chandef.width == NL80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vif.bss_conf.chandef.width == NL80211_CHAN_WIDTH_5 ||
	    sdata->vif.bss_conf.chandef.width == NL80211_CHAN_WIDTH_10)
		return 0;

	if (skb_tailroom(skb) < 2 + sizeof(struct ieee80211_ht_operation))
		return -ENOMEM;

	pos = skb_put(skb, 2 + sizeof(struct ieee80211_ht_operation));
	ieee80211_ie_build_ht_oper(pos, ht_cap, &sdata->vif.bss_conf.chandef,
				   sdata->vif.bss_conf.ht_operation_mode,
				   false);

	return 0;
}