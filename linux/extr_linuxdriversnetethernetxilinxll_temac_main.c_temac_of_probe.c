#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct temac_local {void* regs; void* sdma_regs; TYPE_1__* dev; struct net_device* ndev; void* phy_node; void* tx_irq; void* rx_irq; int /*<<< orphan*/  dma_out; int /*<<< orphan*/  dma_in; int /*<<< orphan*/  temac_features; int /*<<< orphan*/  indirect_mutex; int /*<<< orphan*/  rx_lock; int /*<<< orphan*/  options; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct net_device {int /*<<< orphan*/  features; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  flags; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IFF_MULTICAST ; 
 int /*<<< orphan*/  NETIF_F_IP_CSUM ; 
 int /*<<< orphan*/  NETIF_F_SG ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  TEMAC_FEATURE_RX_CSUM ; 
 int /*<<< orphan*/  TEMAC_FEATURE_TX_CSUM ; 
 int /*<<< orphan*/  XTE_OPTION_DEFAULTS ; 
 struct net_device* alloc_etherdev (int) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,struct device_node*,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 void* irq_of_parse_and_map (struct device_node*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 void* of_get_mac_address (struct device_node*) ; 
 scalar_t__ of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 void* of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 void* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  temac_attr_group ; 
 scalar_t__ temac_dcr_setup (struct temac_local*,struct platform_device*,struct device_node*) ; 
 int /*<<< orphan*/  temac_dma_in32 ; 
 int /*<<< orphan*/  temac_dma_out32 ; 
 int /*<<< orphan*/  temac_ethtool_ops ; 
 int /*<<< orphan*/  temac_init_mac_address (struct net_device*,void const*) ; 
 int temac_mdio_setup (struct temac_local*,struct device_node*) ; 
 int /*<<< orphan*/  temac_netdev_ops ; 

__attribute__((used)) static int temac_of_probe(struct platform_device *op)
{
	struct device_node *np;
	struct temac_local *lp;
	struct net_device *ndev;
	const void *addr;
	__be32 *p;
	int rc = 0;

	/* Init network device structure */
	ndev = alloc_etherdev(sizeof(*lp));
	if (!ndev)
		return -ENOMEM;

	platform_set_drvdata(op, ndev);
	SET_NETDEV_DEV(ndev, &op->dev);
	ndev->flags &= ~IFF_MULTICAST;  /* clear multicast */
	ndev->features = NETIF_F_SG;
	ndev->netdev_ops = &temac_netdev_ops;
	ndev->ethtool_ops = &temac_ethtool_ops;
#if 0
	ndev->features |= NETIF_F_IP_CSUM; /* Can checksum TCP/UDP over IPv4. */
	ndev->features |= NETIF_F_HW_CSUM; /* Can checksum all the packets. */
	ndev->features |= NETIF_F_IPV6_CSUM; /* Can checksum IPV6 TCP/UDP */
	ndev->features |= NETIF_F_HIGHDMA; /* Can DMA to high memory. */
	ndev->features |= NETIF_F_HW_VLAN_CTAG_TX; /* Transmit VLAN hw accel */
	ndev->features |= NETIF_F_HW_VLAN_CTAG_RX; /* Receive VLAN hw acceleration */
	ndev->features |= NETIF_F_HW_VLAN_CTAG_FILTER; /* Receive VLAN filtering */
	ndev->features |= NETIF_F_VLAN_CHALLENGED; /* cannot handle VLAN pkts */
	ndev->features |= NETIF_F_GSO; /* Enable software GSO. */
	ndev->features |= NETIF_F_MULTI_QUEUE; /* Has multiple TX/RX queues */
	ndev->features |= NETIF_F_LRO; /* large receive offload */
#endif

	/* setup temac private info structure */
	lp = netdev_priv(ndev);
	lp->ndev = ndev;
	lp->dev = &op->dev;
	lp->options = XTE_OPTION_DEFAULTS;
	spin_lock_init(&lp->rx_lock);
	mutex_init(&lp->indirect_mutex);

	/* map device registers */
	lp->regs = of_iomap(op->dev.of_node, 0);
	if (!lp->regs) {
		dev_err(&op->dev, "could not map temac regs.\n");
		rc = -ENOMEM;
		goto nodev;
	}

	/* Setup checksum offload, but default to off if not specified */
	lp->temac_features = 0;
	p = (__be32 *)of_get_property(op->dev.of_node, "xlnx,txcsum", NULL);
	if (p && be32_to_cpu(*p)) {
		lp->temac_features |= TEMAC_FEATURE_TX_CSUM;
		/* Can checksum TCP/UDP over IPv4. */
		ndev->features |= NETIF_F_IP_CSUM;
	}
	p = (__be32 *)of_get_property(op->dev.of_node, "xlnx,rxcsum", NULL);
	if (p && be32_to_cpu(*p))
		lp->temac_features |= TEMAC_FEATURE_RX_CSUM;

	/* Find the DMA node, map the DMA registers, and decode the DMA IRQs */
	np = of_parse_phandle(op->dev.of_node, "llink-connected", 0);
	if (!np) {
		dev_err(&op->dev, "could not find DMA node\n");
		rc = -ENODEV;
		goto err_iounmap;
	}

	/* Setup the DMA register accesses, could be DCR or memory mapped */
	if (temac_dcr_setup(lp, op, np)) {

		/* no DCR in the device tree, try non-DCR */
		lp->sdma_regs = of_iomap(np, 0);
		if (lp->sdma_regs) {
			lp->dma_in = temac_dma_in32;
			lp->dma_out = temac_dma_out32;
			dev_dbg(&op->dev, "MEM base: %p\n", lp->sdma_regs);
		} else {
			dev_err(&op->dev, "unable to map DMA registers\n");
			of_node_put(np);
			goto err_iounmap;
		}
	}

	lp->rx_irq = irq_of_parse_and_map(np, 0);
	lp->tx_irq = irq_of_parse_and_map(np, 1);

	of_node_put(np); /* Finished with the DMA node; drop the reference */

	if (!lp->rx_irq || !lp->tx_irq) {
		dev_err(&op->dev, "could not determine irqs\n");
		rc = -ENOMEM;
		goto err_iounmap_2;
	}


	/* Retrieve the MAC address */
	addr = of_get_mac_address(op->dev.of_node);
	if (!addr) {
		dev_err(&op->dev, "could not find MAC address\n");
		rc = -ENODEV;
		goto err_iounmap_2;
	}
	temac_init_mac_address(ndev, addr);

	rc = temac_mdio_setup(lp, op->dev.of_node);
	if (rc)
		dev_warn(&op->dev, "error registering MDIO bus\n");

	lp->phy_node = of_parse_phandle(op->dev.of_node, "phy-handle", 0);
	if (lp->phy_node)
		dev_dbg(lp->dev, "using PHY node %pOF (%p)\n", np, np);

	/* Add the device attributes */
	rc = sysfs_create_group(&lp->dev->kobj, &temac_attr_group);
	if (rc) {
		dev_err(lp->dev, "Error creating sysfs files\n");
		goto err_iounmap_2;
	}

	rc = register_netdev(lp->ndev);
	if (rc) {
		dev_err(lp->dev, "register_netdev() error (%i)\n", rc);
		goto err_register_ndev;
	}

	return 0;

 err_register_ndev:
	sysfs_remove_group(&lp->dev->kobj, &temac_attr_group);
 err_iounmap_2:
	if (lp->sdma_regs)
		iounmap(lp->sdma_regs);
 err_iounmap:
	iounmap(lp->regs);
 nodev:
	free_netdev(ndev);
	ndev = NULL;
	return rc;
}