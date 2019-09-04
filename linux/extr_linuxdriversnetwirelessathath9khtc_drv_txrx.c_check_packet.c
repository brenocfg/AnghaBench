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
struct ath_common {int dummy; } ;
struct ath9k_htc_tx_ctl {scalar_t__ timestamp; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH9K_HTC_TX_TIMEOUT_INTERVAL ; 
 struct ath9k_htc_tx_ctl* HTC_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  XMIT ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline bool check_packet(struct ath9k_htc_priv *priv, struct sk_buff *skb)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct ath9k_htc_tx_ctl *tx_ctl;

	tx_ctl = HTC_SKB_CB(skb);

	if (time_after(jiffies,
		       tx_ctl->timestamp +
		       msecs_to_jiffies(ATH9K_HTC_TX_TIMEOUT_INTERVAL))) {
		ath_dbg(common, XMIT, "Dropping a packet due to TX timeout\n");
		return true;
	}

	return false;
}