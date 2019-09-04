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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct il_priv {int dummy; } ;
struct ieee80211_tx_control {int /*<<< orphan*/  sta; } ;
struct ieee80211_hw {struct il_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  bitrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_MACDUMP (char*) ; 
 int /*<<< orphan*/  D_TX (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 TYPE_1__* ieee80211_get_tx_rate (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ il4965_tx_skb (struct il_priv*,int /*<<< orphan*/ ,struct sk_buff*) ; 

void
il4965_mac_tx(struct ieee80211_hw *hw,
	      struct ieee80211_tx_control *control,
	      struct sk_buff *skb)
{
	struct il_priv *il = hw->priv;

	D_MACDUMP("enter\n");

	D_TX("dev->xmit(%d bytes) at rate 0x%02x\n", skb->len,
	     ieee80211_get_tx_rate(hw, IEEE80211_SKB_CB(skb))->bitrate);

	if (il4965_tx_skb(il, control->sta, skb))
		dev_kfree_skb_any(skb);

	D_MACDUMP("leave\n");
}