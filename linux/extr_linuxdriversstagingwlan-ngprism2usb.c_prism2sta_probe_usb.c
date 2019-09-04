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
struct wlandevice {int /*<<< orphan*/  msdstate; int /*<<< orphan*/  netdev; struct wlandevice* wlandev; struct wlandevice* priv; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct hfa384x {int /*<<< orphan*/  msdstate; int /*<<< orphan*/  netdev; struct hfa384x* wlandev; struct hfa384x* priv; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  P80211ENUM_ifstate_enable ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WLAN_MSD_HWPRESENT ; 
 struct wlandevice* create_wlan () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int hfa384x_corereset (struct wlandevice*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfa384x_create (struct wlandevice*,struct usb_device*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct wlandevice*) ; 
 scalar_t__ prism2_doreset ; 
 int /*<<< orphan*/  prism2_fwtry (struct usb_device*,struct wlandevice*) ; 
 int /*<<< orphan*/  prism2_reset_holdtime ; 
 int /*<<< orphan*/  prism2_reset_settletime ; 
 int /*<<< orphan*/  prism2sta_ifstate (struct wlandevice*,int /*<<< orphan*/ ) ; 
 scalar_t__ register_wlandev (struct wlandevice*) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct wlandevice*) ; 
 scalar_t__ wlan_setup (struct wlandevice*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlan_unsetup (struct wlandevice*) ; 

__attribute__((used)) static int prism2sta_probe_usb(struct usb_interface *interface,
			       const struct usb_device_id *id)
{
	struct usb_device *dev;

	struct wlandevice *wlandev = NULL;
	struct hfa384x *hw = NULL;
	int result = 0;

	dev = interface_to_usbdev(interface);
	wlandev = create_wlan();
	if (!wlandev) {
		dev_err(&interface->dev, "Memory allocation failure.\n");
		result = -EIO;
		goto failed;
	}
	hw = wlandev->priv;

	if (wlan_setup(wlandev, &interface->dev) != 0) {
		dev_err(&interface->dev, "wlan_setup() failed.\n");
		result = -EIO;
		goto failed;
	}

	/* Initialize the hw data */
	hfa384x_create(hw, dev);
	hw->wlandev = wlandev;

	/* Register the wlandev, this gets us a name and registers the
	 * linux netdevice.
	 */
	SET_NETDEV_DEV(wlandev->netdev, &interface->dev);

	/* Do a chip-level reset on the MAC */
	if (prism2_doreset) {
		result = hfa384x_corereset(hw,
					   prism2_reset_holdtime,
					   prism2_reset_settletime, 0);
		if (result != 0) {
			result = -EIO;
			dev_err(&interface->dev,
				"hfa384x_corereset() failed.\n");
			goto failed_reset;
		}
	}

	usb_get_dev(dev);

	wlandev->msdstate = WLAN_MSD_HWPRESENT;

	/* Try and load firmware, then enable card before we register */
	prism2_fwtry(dev, wlandev);
	prism2sta_ifstate(wlandev, P80211ENUM_ifstate_enable);

	if (register_wlandev(wlandev) != 0) {
		dev_err(&interface->dev, "register_wlandev() failed.\n");
		result = -EIO;
		goto failed_register;
	}

	goto done;

failed_register:
	usb_put_dev(dev);
failed_reset:
	wlan_unsetup(wlandev);
failed:
	kfree(wlandev);
	kfree(hw);
	wlandev = NULL;

done:
	usb_set_intfdata(interface, wlandev);
	return result;
}