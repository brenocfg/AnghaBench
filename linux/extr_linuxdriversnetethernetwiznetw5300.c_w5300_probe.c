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
struct w5300_priv {int /*<<< orphan*/  napi; struct net_device* ndev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  features; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  NETIF_F_VLAN_CHALLENGED ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct w5300_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 
 int /*<<< orphan*/  w5300_ethtool_ops ; 
 int w5300_hw_probe (struct platform_device*) ; 
 int /*<<< orphan*/  w5300_napi_poll ; 
 int /*<<< orphan*/  w5300_netdev_ops ; 

__attribute__((used)) static int w5300_probe(struct platform_device *pdev)
{
	struct w5300_priv *priv;
	struct net_device *ndev;
	int err;

	ndev = alloc_etherdev(sizeof(*priv));
	if (!ndev)
		return -ENOMEM;
	SET_NETDEV_DEV(ndev, &pdev->dev);
	platform_set_drvdata(pdev, ndev);
	priv = netdev_priv(ndev);
	priv->ndev = ndev;

	ndev->netdev_ops = &w5300_netdev_ops;
	ndev->ethtool_ops = &w5300_ethtool_ops;
	ndev->watchdog_timeo = HZ;
	netif_napi_add(ndev, &priv->napi, w5300_napi_poll, 16);

	/* This chip doesn't support VLAN packets with normal MTU,
	 * so disable VLAN for this device.
	 */
	ndev->features |= NETIF_F_VLAN_CHALLENGED;

	err = register_netdev(ndev);
	if (err < 0)
		goto err_register;

	err = w5300_hw_probe(pdev);
	if (err < 0)
		goto err_hw_probe;

	return 0;

err_hw_probe:
	unregister_netdev(ndev);
err_register:
	free_netdev(ndev);
	return err;
}