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
struct usb_interface {int dummy; } ;
struct p54u_priv {int (* upload_fw ) (struct ieee80211_hw*) ;scalar_t__ fw; } ;
struct ieee80211_hw {struct p54u_priv* priv; } ;

/* Variables and functions */
 int ENODEV ; 
 int stub1 (struct ieee80211_hw*) ; 
 scalar_t__ unlikely (int) ; 
 struct ieee80211_hw* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int p54u_resume(struct usb_interface *intf)
{
	struct ieee80211_hw *dev = usb_get_intfdata(intf);
	struct p54u_priv *priv;

	if (!dev)
		return -ENODEV;

	priv = dev->priv;
	if (unlikely(!(priv->upload_fw && priv->fw)))
		return 0;

	return priv->upload_fw(dev);
}