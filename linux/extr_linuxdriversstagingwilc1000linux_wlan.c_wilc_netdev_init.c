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
struct wireless_dev {struct net_device* netdev; } ;
struct TYPE_6__ {scalar_t__ tx_bytes; scalar_t__ rx_bytes; scalar_t__ tx_packets; scalar_t__ rx_packets; } ;
struct wilc_vif {int ifc_id; int idx; scalar_t__ mac_opened; int /*<<< orphan*/  iftype; TYPE_3__ netstats; struct net_device* ndev; struct wilc* wilc; } ;
struct wilc_hif_func {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; } ;
struct wilc {int io_type; int vif_num; struct wilc_vif** vif; TYPE_2__ rxq_head; TYPE_1__ txq_head; struct wilc_hif_func const* hif_func; } ;
struct net_device {struct wilc_vif* ml_priv; struct wireless_dev* ieee80211_ptr; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NUM_CONCURRENT_IFC ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 int /*<<< orphan*/  STATION_MODE ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  g_dev_notifier ; 
 struct wilc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct wilc_vif*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_vif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  register_inetaddr_notifier (int /*<<< orphan*/ *) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 struct wireless_dev* wilc_create_wiphy (struct net_device*,struct device*) ; 
 int /*<<< orphan*/  wilc_netdev_ops ; 

int wilc_netdev_init(struct wilc **wilc, struct device *dev, int io_type,
		     const struct wilc_hif_func *ops)
{
	int i, ret;
	struct wilc_vif *vif;
	struct net_device *ndev;
	struct wilc *wl;

	wl = kzalloc(sizeof(*wl), GFP_KERNEL);
	if (!wl)
		return -ENOMEM;

	*wilc = wl;
	wl->io_type = io_type;
	wl->hif_func = ops;
	INIT_LIST_HEAD(&wl->txq_head.list);
	INIT_LIST_HEAD(&wl->rxq_head.list);

	register_inetaddr_notifier(&g_dev_notifier);

	for (i = 0; i < NUM_CONCURRENT_IFC; i++) {
		struct wireless_dev *wdev;

		ndev = alloc_etherdev(sizeof(struct wilc_vif));
		if (!ndev)
			return -ENOMEM;

		vif = netdev_priv(ndev);
		memset(vif, 0, sizeof(struct wilc_vif));

		if (i == 0) {
			strcpy(ndev->name, "wlan%d");
			vif->ifc_id = 1;
		} else {
			strcpy(ndev->name, "p2p%d");
			vif->ifc_id = 0;
		}
		vif->wilc = *wilc;
		vif->ndev = ndev;
		wl->vif[i] = vif;
		wl->vif_num = i + 1;
		vif->idx = i;

		ndev->netdev_ops = &wilc_netdev_ops;

		wdev = wilc_create_wiphy(ndev, dev);

		if (dev)
			SET_NETDEV_DEV(ndev, dev);

		if (!wdev) {
			netdev_err(ndev, "Can't register WILC Wiphy\n");
			return -1;
		}

		vif->ndev->ieee80211_ptr = wdev;
		vif->ndev->ml_priv = vif;
		wdev->netdev = vif->ndev;
		vif->netstats.rx_packets = 0;
		vif->netstats.tx_packets = 0;
		vif->netstats.rx_bytes = 0;
		vif->netstats.tx_bytes = 0;

		ret = register_netdev(ndev);
		if (ret)
			return ret;

		vif->iftype = STATION_MODE;
		vif->mac_opened = 0;
	}

	return 0;
}