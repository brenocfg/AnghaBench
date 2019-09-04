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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct mt76_wcid {int hw_key_idx; scalar_t__ sw_iv; } ;
struct ieee80211_tx_info {int flags; } ;
typedef  enum mt76x2_qsel { ____Placeholder_mt76x2_qsel } mt76x2_qsel ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_RATE_CTRL_PROBE ; 
 scalar_t__ MT_EP_OUT_HCCA ; 
 int MT_QSEL_EDCA ; 
 int MT_QSEL_MGMT ; 
 int MT_TXD_INFO_80211 ; 
 int /*<<< orphan*/  MT_TXD_INFO_QSEL ; 
 int MT_TXD_INFO_WIV ; 
 int /*<<< orphan*/  WLAN_PORT ; 
 int mt76u_skb_dma_info (struct sk_buff*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mt76x2u_set_txinfo(struct sk_buff *skb,
		   struct mt76_wcid *wcid, u8 ep)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	enum mt76x2_qsel qsel;
	u32 flags;

	if ((info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE) ||
	    ep == MT_EP_OUT_HCCA)
		qsel = MT_QSEL_MGMT;
	else
		qsel = MT_QSEL_EDCA;

	flags = FIELD_PREP(MT_TXD_INFO_QSEL, qsel) |
		MT_TXD_INFO_80211;
	if (!wcid || wcid->hw_key_idx == 0xff || wcid->sw_iv)
		flags |= MT_TXD_INFO_WIV;

	return mt76u_skb_dma_info(skb, WLAN_PORT, flags);
}