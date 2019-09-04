#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int phy_id_mask; int reg_num_mask; int /*<<< orphan*/  mdio_write; int /*<<< orphan*/  mdio_read; struct net_device* dev; } ;
struct smc_private {TYPE_1__ mii_if; int /*<<< orphan*/  lock; struct pcmcia_device* p_dev; } ;
struct pcmcia_device {struct net_device* priv; int /*<<< orphan*/  dev; } ;
struct net_device {int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ethtool_ops ; 
 int /*<<< orphan*/  mdio_read ; 
 int /*<<< orphan*/  mdio_write ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int smc91c92_config (struct pcmcia_device*) ; 
 int /*<<< orphan*/  smc_netdev_ops ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smc91c92_probe(struct pcmcia_device *link)
{
    struct smc_private *smc;
    struct net_device *dev;

    dev_dbg(&link->dev, "smc91c92_attach()\n");

    /* Create new ethernet device */
    dev = alloc_etherdev(sizeof(struct smc_private));
    if (!dev)
	return -ENOMEM;
    smc = netdev_priv(dev);
    smc->p_dev = link;
    link->priv = dev;

    spin_lock_init(&smc->lock);

    /* The SMC91c92-specific entries in the device structure. */
    dev->netdev_ops = &smc_netdev_ops;
    dev->ethtool_ops = &ethtool_ops;
    dev->watchdog_timeo = TX_TIMEOUT;

    smc->mii_if.dev = dev;
    smc->mii_if.mdio_read = mdio_read;
    smc->mii_if.mdio_write = mdio_write;
    smc->mii_if.phy_id_mask = 0x1f;
    smc->mii_if.reg_num_mask = 0x1f;

    return smc91c92_config(link);
}