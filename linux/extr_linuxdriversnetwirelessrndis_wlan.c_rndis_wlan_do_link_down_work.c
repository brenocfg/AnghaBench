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
struct usbnet {int /*<<< orphan*/  net; } ;
struct rndis_wlan_private {int connected; int /*<<< orphan*/  bssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cfg80211_disconnected (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deauthenticate (struct usbnet*) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 struct rndis_wlan_private* get_rndis_wlan_priv (struct usbnet*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rndis_wlan_do_link_down_work(struct usbnet *usbdev)
{
	struct rndis_wlan_private *priv = get_rndis_wlan_priv(usbdev);

	if (priv->connected) {
		priv->connected = false;
		eth_zero_addr(priv->bssid);

		deauthenticate(usbdev);

		cfg80211_disconnected(usbdev->net, 0, NULL, 0, true, GFP_KERNEL);
	}

	netif_carrier_off(usbdev->net);
}