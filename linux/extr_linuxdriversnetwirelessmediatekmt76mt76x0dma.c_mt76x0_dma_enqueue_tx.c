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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;
struct mt76x0_dev {TYPE_1__ mt76; } ;
struct mt76_wcid {int hw_key_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_TXD_PKT_INFO_80211 ; 
 int /*<<< orphan*/  MT_TXD_PKT_INFO_WIV ; 
 int /*<<< orphan*/  ep2dmaq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int mt76x0_dma_skb_wrap_pkt (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt76x0_dma_submit_tx (struct mt76x0_dev*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q2ep (int) ; 

int mt76x0_dma_enqueue_tx(struct mt76x0_dev *dev, struct sk_buff *skb,
			   struct mt76_wcid *wcid, int hw_q)
{
	u8 ep = q2ep(hw_q);
	u32 dma_flags;
	int ret;

	dma_flags = MT_TXD_PKT_INFO_80211;
	if (wcid->hw_key_idx == 0xff)
		dma_flags |= MT_TXD_PKT_INFO_WIV;

	ret = mt76x0_dma_skb_wrap_pkt(skb, ep2dmaq(ep), dma_flags);
	if (ret)
		return ret;

	ret = mt76x0_dma_submit_tx(dev, skb, ep);

	if (ret) {
		ieee80211_free_txskb(dev->mt76.hw, skb);
		return ret;
	}

	return 0;
}