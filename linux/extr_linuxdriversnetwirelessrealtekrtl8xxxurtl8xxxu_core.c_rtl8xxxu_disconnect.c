#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int dummy; } ;
struct rtl8xxxu_priv {TYPE_2__* udev; int /*<<< orphan*/  h2c_mutex; int /*<<< orphan*/  usb_buf_mutex; int /*<<< orphan*/  fw_data; TYPE_1__* fops; } ;
struct ieee80211_hw {struct rtl8xxxu_priv* priv; } ;
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* power_off ) (struct rtl8xxxu_priv*) ;} ;

/* Variables and functions */
 scalar_t__ USB_STATE_NOTATTACHED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rtl8xxxu_priv*) ; 
 struct ieee80211_hw* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_put_dev (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_reset_device (TYPE_2__*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl8xxxu_disconnect(struct usb_interface *interface)
{
	struct rtl8xxxu_priv *priv;
	struct ieee80211_hw *hw;

	hw = usb_get_intfdata(interface);
	priv = hw->priv;

	ieee80211_unregister_hw(hw);

	priv->fops->power_off(priv);

	usb_set_intfdata(interface, NULL);

	dev_info(&priv->udev->dev, "disconnecting\n");

	kfree(priv->fw_data);
	mutex_destroy(&priv->usb_buf_mutex);
	mutex_destroy(&priv->h2c_mutex);

	if (priv->udev->state != USB_STATE_NOTATTACHED) {
		dev_info(&priv->udev->dev,
			 "Device still attached, trying to reset\n");
		usb_reset_device(priv->udev);
	}
	usb_put_dev(priv->udev);
	ieee80211_free_hw(hw);
}