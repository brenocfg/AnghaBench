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
struct vnt_private {int /*<<< orphan*/  hw; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 struct sk_buff* ieee80211_beacon_get (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ vnt_beacon_xmit (struct vnt_private*,struct sk_buff*) ; 

int vnt_beacon_make(struct vnt_private *priv, struct ieee80211_vif *vif)
{
	struct sk_buff *beacon;

	beacon = ieee80211_beacon_get(priv->hw, vif);
	if (!beacon)
		return -ENOMEM;

	if (vnt_beacon_xmit(priv, beacon)) {
		ieee80211_free_txskb(priv->hw, beacon);
		return -ENODEV;
	}

	return 0;
}