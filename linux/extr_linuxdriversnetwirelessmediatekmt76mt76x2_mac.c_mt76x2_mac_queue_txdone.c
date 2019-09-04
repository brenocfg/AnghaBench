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
struct mt76x2_txwi {int /*<<< orphan*/  pktid; int /*<<< orphan*/  wcid; } ;
struct mt76x2_tx_info {int /*<<< orphan*/  pktid; int /*<<< orphan*/  wcid; int /*<<< orphan*/  jiffies; scalar_t__ tries; } ;
struct mt76x2_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mt76x2_mac_poll_tx_status (struct mt76x2_dev*,int) ; 
 struct mt76x2_tx_info* mt76x2_skb_tx_info (struct sk_buff*) ; 
 int /*<<< orphan*/  mt76x2_tx_complete (struct mt76x2_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  trace_mac_txdone_add (struct mt76x2_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt76x2_mac_queue_txdone(struct mt76x2_dev *dev, struct sk_buff *skb,
			void *txwi_ptr)
{
	struct mt76x2_tx_info *txi = mt76x2_skb_tx_info(skb);
	struct mt76x2_txwi *txwi = txwi_ptr;

	mt76x2_mac_poll_tx_status(dev, false);

	txi->tries = 0;
	txi->jiffies = jiffies;
	txi->wcid = txwi->wcid;
	txi->pktid = txwi->pktid;
	trace_mac_txdone_add(dev, txwi->wcid, txwi->pktid);
	mt76x2_tx_complete(dev, skb);
}