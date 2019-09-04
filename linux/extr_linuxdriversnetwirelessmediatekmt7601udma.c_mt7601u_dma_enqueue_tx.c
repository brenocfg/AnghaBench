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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct mt76_wcid {int hw_key_idx; } ;
struct mt7601u_dev {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_TXD_PKT_INFO_80211 ; 
 int /*<<< orphan*/  MT_TXD_PKT_INFO_WIV ; 
 int /*<<< orphan*/  ep2dmaq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int mt7601u_dma_skb_wrap_pkt (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt7601u_dma_submit_tx (struct mt7601u_dev*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q2ep (int) ; 

int mt7601u_dma_enqueue_tx(struct mt7601u_dev *dev, struct sk_buff *skb,
			   struct mt76_wcid *wcid, int hw_q)
{
	u8 ep = q2ep(hw_q);
	u32 dma_flags;
	int ret;

	dma_flags = MT_TXD_PKT_INFO_80211;
	if (wcid->hw_key_idx == 0xff)
		dma_flags |= MT_TXD_PKT_INFO_WIV;

	ret = mt7601u_dma_skb_wrap_pkt(skb, ep2dmaq(ep), dma_flags);
	if (ret)
		return ret;

	ret = mt7601u_dma_submit_tx(dev, skb, ep);
	if (ret) {
		ieee80211_free_txskb(dev->hw, skb);
		return ret;
	}

	return 0;
}