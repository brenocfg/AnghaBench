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
struct urb {int dummy; } ;
struct rtl_usb {int rx_urb_num; int rx_max_size; int /*<<< orphan*/  rx_submitted; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int _rtl_prep_rx_urb (struct ieee80211_hw*,struct rtl_usb*,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl_usb_cleanup_rx (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rtl_usb* rtl_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_usbpriv (struct ieee80211_hw*) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_anchor_urb (struct urb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _rtl_usb_receive(struct ieee80211_hw *hw)
{
	struct urb *urb;
	int err;
	int i;
	struct rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	WARN_ON(0 == rtlusb->rx_urb_num);
	/* 1600 == 1514 + max WLAN header + rtk info */
	WARN_ON(rtlusb->rx_max_size < 1600);

	for (i = 0; i < rtlusb->rx_urb_num; i++) {
		err = -ENOMEM;
		urb = usb_alloc_urb(0, GFP_KERNEL);
		if (!urb)
			goto err_out;

		err = _rtl_prep_rx_urb(hw, rtlusb, urb, GFP_KERNEL);
		if (err < 0) {
			pr_err("Failed to prep_rx_urb!!\n");
			usb_free_urb(urb);
			goto err_out;
		}

		usb_anchor_urb(urb, &rtlusb->rx_submitted);
		err = usb_submit_urb(urb, GFP_KERNEL);
		if (err)
			goto err_out;
		usb_free_urb(urb);
	}
	return 0;

err_out:
	usb_kill_anchored_urbs(&rtlusb->rx_submitted);
	_rtl_usb_cleanup_rx(hw);
	return err;
}