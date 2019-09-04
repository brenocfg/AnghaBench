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
struct wilc_wfi_mon_priv {struct net_device* real_ndev; } ;
struct net_device {int /*<<< orphan*/ * netdev_ops; scalar_t__* name; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IEEE80211_RADIOTAP ; 
 int IFNAMSIZ ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct wilc_wfi_mon_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ register_netdevice (struct net_device*) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,char const*,int) ; 
 struct net_device* wilc_wfi_mon ; 
 int /*<<< orphan*/  wilc_wfi_netdev_ops ; 

struct net_device *wilc_wfi_init_mon_interface(const char *name,
					       struct net_device *real_dev)
{
	struct wilc_wfi_mon_priv *priv;

	/*If monitor interface is already initialized, return it*/
	if (wilc_wfi_mon)
		return wilc_wfi_mon;

	wilc_wfi_mon = alloc_etherdev(sizeof(struct wilc_wfi_mon_priv));
	if (!wilc_wfi_mon)
		return NULL;
	wilc_wfi_mon->type = ARPHRD_IEEE80211_RADIOTAP;
	strncpy(wilc_wfi_mon->name, name, IFNAMSIZ);
	wilc_wfi_mon->name[IFNAMSIZ - 1] = 0;
	wilc_wfi_mon->netdev_ops = &wilc_wfi_netdev_ops;

	if (register_netdevice(wilc_wfi_mon)) {
		netdev_err(real_dev, "register_netdevice failed\n");
		return NULL;
	}
	priv = netdev_priv(wilc_wfi_mon);
	if (!priv)
		return NULL;

	priv->real_ndev = real_dev;

	return wilc_wfi_mon;
}