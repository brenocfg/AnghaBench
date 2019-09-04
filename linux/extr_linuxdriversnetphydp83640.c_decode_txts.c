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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {scalar_t__ cb; } ;
struct phy_txts {int ns_hi; } ;
struct dp83640_skb_info {int /*<<< orphan*/  tmo; } ;
struct dp83640_private {int /*<<< orphan*/  tx_queue; } ;
typedef  int /*<<< orphan*/  shhwtstamps ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy2txts (struct phy_txts*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  skb_complete_tx_timestamp (struct sk_buff*,struct skb_shared_hwtstamps*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decode_txts(struct dp83640_private *dp83640,
			struct phy_txts *phy_txts)
{
	struct skb_shared_hwtstamps shhwtstamps;
	struct dp83640_skb_info *skb_info;
	struct sk_buff *skb;
	u8 overflow;
	u64 ns;

	/* We must already have the skb that triggered this. */
again:
	skb = skb_dequeue(&dp83640->tx_queue);
	if (!skb) {
		pr_debug("have timestamp but tx_queue empty\n");
		return;
	}

	overflow = (phy_txts->ns_hi >> 14) & 0x3;
	if (overflow) {
		pr_debug("tx timestamp queue overflow, count %d\n", overflow);
		while (skb) {
			kfree_skb(skb);
			skb = skb_dequeue(&dp83640->tx_queue);
		}
		return;
	}
	skb_info = (struct dp83640_skb_info *)skb->cb;
	if (time_after(jiffies, skb_info->tmo)) {
		kfree_skb(skb);
		goto again;
	}

	ns = phy2txts(phy_txts);
	memset(&shhwtstamps, 0, sizeof(shhwtstamps));
	shhwtstamps.hwtstamp = ns_to_ktime(ns);
	skb_complete_tx_timestamp(skb, &shhwtstamps);
}