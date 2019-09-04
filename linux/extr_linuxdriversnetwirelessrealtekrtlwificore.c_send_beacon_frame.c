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
struct sk_buff {int dummy; } ;
struct rtl_tcb_desc {int dummy; } ;
struct rtl_priv {TYPE_1__* intf_ops; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* adapter_tx ) (struct ieee80211_hw*,int /*<<< orphan*/ *,struct sk_buff*,struct rtl_tcb_desc*) ;} ;

/* Variables and functions */
 struct sk_buff* ieee80211_beacon_get (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  memset (struct rtl_tcb_desc*,int /*<<< orphan*/ ,int) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int /*<<< orphan*/ *,struct sk_buff*,struct rtl_tcb_desc*) ; 

__attribute__((used)) static void send_beacon_frame(struct ieee80211_hw *hw,
			      struct ieee80211_vif *vif)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct sk_buff *skb = ieee80211_beacon_get(hw, vif);
	struct rtl_tcb_desc tcb_desc;

	if (skb) {
		memset(&tcb_desc, 0, sizeof(struct rtl_tcb_desc));
		rtlpriv->intf_ops->adapter_tx(hw, NULL, skb, &tcb_desc);
	}
}