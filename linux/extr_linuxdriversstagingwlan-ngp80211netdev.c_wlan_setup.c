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
struct wlandevice {struct net_device* netdev; int /*<<< orphan*/  rx_bh; int /*<<< orphan*/  nsd_rxq; int /*<<< orphan*/  macmode; int /*<<< orphan*/  ethconv; int /*<<< orphan*/  state; } ;
struct wireless_dev {int /*<<< orphan*/  iftype; struct wiphy* wiphy; } ;
struct wiphy {int dummy; } ;
struct net_device {int min_mtu; int max_mtu; struct wireless_dev* ieee80211_ptr; int /*<<< orphan*/ * netdev_ops; struct wlandevice* ml_priv; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  WLAN_DEVICE_CLOSED ; 
 int /*<<< orphan*/  WLAN_ETHCONV_8021h ; 
 int /*<<< orphan*/  WLAN_MACMODE_NONE ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  ether_setup ; 
 struct wireless_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  p80211_netdev_ops ; 
 int /*<<< orphan*/  p80211netdev_rx_bh ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 struct wiphy* wlan_create_wiphy (struct device*,struct wlandevice*) ; 
 int /*<<< orphan*/  wlan_free_wiphy (struct wiphy*) ; 

int wlan_setup(struct wlandevice *wlandev, struct device *physdev)
{
	int result = 0;
	struct net_device *netdev;
	struct wiphy *wiphy;
	struct wireless_dev *wdev;

	/* Set up the wlandev */
	wlandev->state = WLAN_DEVICE_CLOSED;
	wlandev->ethconv = WLAN_ETHCONV_8021h;
	wlandev->macmode = WLAN_MACMODE_NONE;

	/* Set up the rx queue */
	skb_queue_head_init(&wlandev->nsd_rxq);
	tasklet_init(&wlandev->rx_bh,
		     p80211netdev_rx_bh, (unsigned long)wlandev);

	/* Allocate and initialize the wiphy struct */
	wiphy = wlan_create_wiphy(physdev, wlandev);
	if (!wiphy) {
		dev_err(physdev, "Failed to alloc wiphy.\n");
		return 1;
	}

	/* Allocate and initialize the struct device */
	netdev = alloc_netdev(sizeof(struct wireless_dev), "wlan%d",
			      NET_NAME_UNKNOWN, ether_setup);
	if (!netdev) {
		dev_err(physdev, "Failed to alloc netdev.\n");
		wlan_free_wiphy(wiphy);
		result = 1;
	} else {
		wlandev->netdev = netdev;
		netdev->ml_priv = wlandev;
		netdev->netdev_ops = &p80211_netdev_ops;
		wdev = netdev_priv(netdev);
		wdev->wiphy = wiphy;
		wdev->iftype = NL80211_IFTYPE_STATION;
		netdev->ieee80211_ptr = wdev;
		netdev->min_mtu = 68;
		/* 2312 is max 802.11 payload, 20 is overhead,
		 * (ether + llc + snap) and another 8 for wep.
		 */
		netdev->max_mtu = (2312 - 20 - 8);

		netif_stop_queue(netdev);
		netif_carrier_off(netdev);
	}

	return result;
}