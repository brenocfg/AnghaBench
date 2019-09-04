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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_sub_if_data {TYPE_1__ vif; } ;
struct ieee80211_channel {int /*<<< orphan*/  center_freq; } ;
struct TYPE_4__ {struct ieee80211_channel* chan; } ;
struct ieee80211_chanctx_conf {TYPE_2__ def; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WLAN_EID_DS_PARAMS ; 
 int /*<<< orphan*/  ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/ * skb_put (struct sk_buff*,int) ; 
 int skb_tailroom (struct sk_buff*) ; 

__attribute__((used)) static int mesh_add_ds_params_ie(struct ieee80211_sub_if_data *sdata,
				 struct sk_buff *skb)
{
	struct ieee80211_chanctx_conf *chanctx_conf;
	struct ieee80211_channel *chan;
	u8 *pos;

	if (skb_tailroom(skb) < 3)
		return -ENOMEM;

	rcu_read_lock();
	chanctx_conf = rcu_dereference(sdata->vif.chanctx_conf);
	if (WARN_ON(!chanctx_conf)) {
		rcu_read_unlock();
		return -EINVAL;
	}
	chan = chanctx_conf->def.chan;
	rcu_read_unlock();

	pos = skb_put(skb, 2 + 1);
	*pos++ = WLAN_EID_DS_PARAMS;
	*pos++ = 1;
	*pos++ = ieee80211_frequency_to_channel(chan->center_freq);

	return 0;
}