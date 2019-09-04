#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtl_usb {int dummy; } ;
struct rtl_priv {TYPE_2__* cfg; } ;
struct rtl_hal {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* hw_init ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SET_USB_START (struct rtl_usb*) ; 
 int _rtl_usb_receive (struct ieee80211_hw*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 int /*<<< orphan*/  rtl_init_rx_config (struct ieee80211_hw*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_usb* rtl_usbdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_usbpriv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  set_hal_start (struct rtl_hal*) ; 
 int stub1 (struct ieee80211_hw*) ; 

__attribute__((used)) static int rtl_usb_start(struct ieee80211_hw *hw)
{
	int err;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_usb *rtlusb = rtl_usbdev(rtl_usbpriv(hw));

	err = rtlpriv->cfg->ops->hw_init(hw);
	if (!err) {
		rtl_init_rx_config(hw);

		/* Enable software */
		SET_USB_START(rtlusb);
		/* should after adapter start and interrupt enable. */
		set_hal_start(rtlhal);

		/* Start bulk IN */
		err = _rtl_usb_receive(hw);
	}

	return err;
}