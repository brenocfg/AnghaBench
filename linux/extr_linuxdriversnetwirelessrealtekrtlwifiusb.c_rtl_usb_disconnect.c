#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct rtl_usb {int /*<<< orphan*/  udev; } ;
struct rtl_priv {TYPE_3__* cfg; int /*<<< orphan*/  usb_data; TYPE_1__* intf_ops; int /*<<< orphan*/  status; int /*<<< orphan*/  firmware_loading_complete; } ;
struct rtl_mac {int mac80211_registered; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* deinit_sw_vars ) (struct ieee80211_hw*) ;int /*<<< orphan*/  (* deinit_sw_leds ) (struct ieee80211_hw*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* adapter_stop ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RTL_STATUS_INTERFACE_START ; 
 int /*<<< orphan*/  _rtl_usb_io_handler_release (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_deinit_core (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_deinit_deferred_work (struct ieee80211_hw*,int) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_usb_deinit (struct ieee80211_hw*) ; 
 struct rtl_usb* rtl_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_usbpriv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub3 (struct ieee80211_hw*) ; 
 scalar_t__ unlikely (int) ; 
 struct ieee80211_hw* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void rtl_usb_disconnect(struct usb_interface *intf)
{
	struct ieee80211_hw *hw = usb_get_intfdata(intf);
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *rtlmac = rtl_mac(rtl_priv(hw));
	struct rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	if (unlikely(!rtlpriv))
		return;
	/* just in case driver is removed before firmware callback */
	wait_for_completion(&rtlpriv->firmware_loading_complete);
	clear_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status);
	/*ieee80211_unregister_hw will call ops_stop */
	if (rtlmac->mac80211_registered == 1) {
		ieee80211_unregister_hw(hw);
		rtlmac->mac80211_registered = 0;
	} else {
		rtl_deinit_deferred_work(hw, false);
		rtlpriv->intf_ops->adapter_stop(hw);
	}
	/*deinit rfkill */
	/* rtl_deinit_rfkill(hw); */
	rtl_usb_deinit(hw);
	rtl_deinit_core(hw);
	kfree(rtlpriv->usb_data);
	rtlpriv->cfg->ops->deinit_sw_leds(hw);
	rtlpriv->cfg->ops->deinit_sw_vars(hw);
	_rtl_usb_io_handler_release(hw);
	usb_put_dev(rtlusb->udev);
	usb_set_intfdata(intf, NULL);
	ieee80211_free_hw(hw);
}