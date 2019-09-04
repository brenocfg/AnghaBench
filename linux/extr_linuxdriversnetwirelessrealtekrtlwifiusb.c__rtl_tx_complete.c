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
struct urb {scalar_t__ context; } ;
struct sk_buff {int dummy; } ;
struct rtl_usb {int /*<<< orphan*/  intf; } ;
struct ieee80211_tx_info {scalar_t__* rate_driver_data; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IS_USB_STOP (struct rtl_usb*) ; 
 int _usb_tx_post (struct ieee80211_hw*,struct urb*,struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct ieee80211_hw* usb_get_intfdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rtl_tx_complete(struct urb *urb)
{
	struct sk_buff *skb = (struct sk_buff *)urb->context;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct rtl_usb *rtlusb = (struct rtl_usb *)info->rate_driver_data[0];
	struct ieee80211_hw *hw = usb_get_intfdata(rtlusb->intf);
	int err;

	if (unlikely(IS_USB_STOP(rtlusb)))
		return;
	err = _usb_tx_post(hw, urb, skb);
	if (err) {
		/* Ignore error and keep issuiing other urbs */
		return;
	}
}