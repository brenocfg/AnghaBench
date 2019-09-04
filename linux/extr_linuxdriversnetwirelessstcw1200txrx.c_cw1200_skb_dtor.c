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
struct sk_buff {int dummy; } ;
struct cw1200_txpriv {scalar_t__ rate_id; int /*<<< orphan*/  tid; int /*<<< orphan*/  raw_link_id; int /*<<< orphan*/  offset; } ;
struct cw1200_common {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 scalar_t__ CW1200_INVALID_RATE_ID ; 
 int /*<<< orphan*/  cw1200_notify_buffered_tx (struct cw1200_common*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_tx_status (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tx_policy_put (struct cw1200_common*,scalar_t__) ; 

void cw1200_skb_dtor(struct cw1200_common *priv,
		     struct sk_buff *skb,
		     const struct cw1200_txpriv *txpriv)
{
	skb_pull(skb, txpriv->offset);
	if (txpriv->rate_id != CW1200_INVALID_RATE_ID) {
		cw1200_notify_buffered_tx(priv, skb,
					  txpriv->raw_link_id, txpriv->tid);
		tx_policy_put(priv, txpriv->rate_id);
	}
	ieee80211_tx_status(priv->hw, skb);
}