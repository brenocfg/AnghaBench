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
struct urb {int status; } ;
struct sk_buff {int dummy; } ;
struct rtl_usb {int /*<<< orphan*/  (* usb_tx_post_hdl ) (struct ieee80211_hw*,struct urb*,struct sk_buff*) ;} ;
struct ieee80211_tx_info {int /*<<< orphan*/  flags; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  RTL_TX_HEADER_SIZE ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_status_irqsafe (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct rtl_usb* rtl_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_usbpriv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,struct urb*,struct sk_buff*) ; 

__attribute__((used)) static int _usb_tx_post(struct ieee80211_hw *hw, struct urb *urb,
			struct sk_buff *skb)
{
	struct rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));
	struct ieee80211_tx_info *txinfo;

	rtlusb->usb_tx_post_hdl(hw, urb, skb);
	skb_pull(skb, RTL_TX_HEADER_SIZE);
	txinfo = IEEE80211_SKB_CB(skb);
	ieee80211_tx_info_clear_status(txinfo);
	txinfo->flags |= IEEE80211_TX_STAT_ACK;

	if (urb->status) {
		pr_err("Urb has error status 0x%X\n", urb->status);
		goto out;
	}
	/*  TODO:	statistics */
out:
	ieee80211_tx_status_irqsafe(hw, skb);
	return urb->status;
}