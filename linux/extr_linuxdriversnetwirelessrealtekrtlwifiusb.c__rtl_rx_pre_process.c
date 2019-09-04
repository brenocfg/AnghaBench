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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct rtl_usb {int /*<<< orphan*/  (* usb_rx_segregate_hdl ) (struct ieee80211_hw*,struct sk_buff*,struct sk_buff_head*) ;} ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl_usb_rx_process_agg (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_rx (struct ieee80211_hw*,struct sk_buff*) ; 
 struct rtl_usb* rtl_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_usbpriv (struct ieee80211_hw*) ; 
 struct sk_buff* skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_empty (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,struct sk_buff*,struct sk_buff_head*) ; 

__attribute__((used)) static void _rtl_rx_pre_process(struct ieee80211_hw *hw, struct sk_buff *skb)
{
	struct sk_buff *_skb;
	struct sk_buff_head rx_queue;
	struct rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	skb_queue_head_init(&rx_queue);
	if (rtlusb->usb_rx_segregate_hdl)
		rtlusb->usb_rx_segregate_hdl(hw, skb, &rx_queue);
	WARN_ON(skb_queue_empty(&rx_queue));
	while (!skb_queue_empty(&rx_queue)) {
		_skb = skb_dequeue(&rx_queue);
		_rtl_usb_rx_process_agg(hw, _skb);
		ieee80211_rx(hw, _skb);
	}
}