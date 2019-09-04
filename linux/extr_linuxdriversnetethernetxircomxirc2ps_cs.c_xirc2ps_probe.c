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
struct pcmcia_device {int config_index; struct net_device* priv; int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct local_info {int /*<<< orphan*/  tx_timeout_task; struct pcmcia_device* p_dev; struct net_device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  netdev_ethtool_ops ; 
 int /*<<< orphan*/  netdev_ops ; 
 struct local_info* netdev_priv (struct net_device*) ; 
 int xirc2ps_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  xirc2ps_tx_timeout_task ; 

__attribute__((used)) static int
xirc2ps_probe(struct pcmcia_device *link)
{
    struct net_device *dev;
    struct local_info *local;

    dev_dbg(&link->dev, "attach()\n");

    /* Allocate the device structure */
    dev = alloc_etherdev(sizeof(struct local_info));
    if (!dev)
	    return -ENOMEM;
    local = netdev_priv(dev);
    local->dev = dev;
    local->p_dev = link;
    link->priv = dev;

    /* General socket configuration */
    link->config_index = 1;

    /* Fill in card specific entries */
    dev->netdev_ops = &netdev_ops;
    dev->ethtool_ops = &netdev_ethtool_ops;
    dev->watchdog_timeo = TX_TIMEOUT;
    INIT_WORK(&local->tx_timeout_task, xirc2ps_tx_timeout_task);

    return xirc2ps_config(link);
}