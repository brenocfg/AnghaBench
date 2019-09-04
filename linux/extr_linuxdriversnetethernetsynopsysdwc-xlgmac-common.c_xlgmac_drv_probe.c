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
struct xlgmac_resources {int /*<<< orphan*/  addr; int /*<<< orphan*/  irq; } ;
struct xlgmac_pdata {int /*<<< orphan*/  msg_enable; int /*<<< orphan*/  rss_mutex; int /*<<< orphan*/  mac_regs; int /*<<< orphan*/  dev_irq; struct net_device* netdev; struct device* dev; } ;
struct net_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,struct device*) ; 
 int /*<<< orphan*/  XLGMAC_MAX_DMA_CHANNELS ; 
 struct net_device* alloc_etherdev_mq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  default_msg_level ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct xlgmac_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int xlgmac_init (struct xlgmac_pdata*) ; 

int xlgmac_drv_probe(struct device *dev, struct xlgmac_resources *res)
{
	struct xlgmac_pdata *pdata;
	struct net_device *netdev;
	int ret;

	netdev = alloc_etherdev_mq(sizeof(struct xlgmac_pdata),
				   XLGMAC_MAX_DMA_CHANNELS);

	if (!netdev) {
		dev_err(dev, "alloc_etherdev failed\n");
		return -ENOMEM;
	}

	SET_NETDEV_DEV(netdev, dev);
	dev_set_drvdata(dev, netdev);
	pdata = netdev_priv(netdev);
	pdata->dev = dev;
	pdata->netdev = netdev;

	pdata->dev_irq = res->irq;
	pdata->mac_regs = res->addr;

	mutex_init(&pdata->rss_mutex);
	pdata->msg_enable = netif_msg_init(debug, default_msg_level);

	ret = xlgmac_init(pdata);
	if (ret) {
		dev_err(dev, "xlgmac init failed\n");
		goto err_free_netdev;
	}

	ret = register_netdev(netdev);
	if (ret) {
		dev_err(dev, "net device registration failed\n");
		goto err_free_netdev;
	}

	return 0;

err_free_netdev:
	free_netdev(netdev);

	return ret;
}