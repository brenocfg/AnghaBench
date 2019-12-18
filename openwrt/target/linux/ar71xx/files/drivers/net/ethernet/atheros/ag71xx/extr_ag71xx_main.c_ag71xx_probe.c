#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct TYPE_16__ {struct ag71xx_platform_data* platform_data; } ;
struct platform_device {TYPE_5__ dev; } ;
struct net_device {unsigned long base_addr; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; } ;
struct ag71xx_platform_data {int /*<<< orphan*/  phy_if_mode; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  is_ar91xx; int /*<<< orphan*/  is_ar724x; scalar_t__ desc_pktlen_mask; scalar_t__ max_frame_len; scalar_t__ phy_mask; int /*<<< orphan*/ * mii_bus_dev; } ;
struct ag71xx_desc {int dummy; } ;
struct TYPE_13__ {void* order; int /*<<< orphan*/  desc_split; } ;
struct TYPE_12__ {void* order; } ;
struct TYPE_14__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct ag71xx {scalar_t__ mac_base; int /*<<< orphan*/  napi; scalar_t__ stop_desc_dma; TYPE_4__* stop_desc; TYPE_2__ tx_ring; scalar_t__ desc_pktlen_mask; scalar_t__ max_frame_len; TYPE_1__ rx_ring; TYPE_3__ oom_timer; int /*<<< orphan*/  restart_work; int /*<<< orphan*/  lock; int /*<<< orphan*/  msg_enable; struct net_device* dev; struct platform_device* pdev; } ;
struct TYPE_15__ {scalar_t__ next; scalar_t__ ctrl; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_DEFAULT_MSG_ENABLE ; 
 int /*<<< orphan*/  AG71XX_NAPI_WEIGHT ; 
 int /*<<< orphan*/  AG71XX_REG_MAC_CFG1 ; 
 int AG71XX_RX_RING_SIZE_DEFAULT ; 
 int AG71XX_TX_RING_DS_PER_PKT ; 
 int AG71XX_TX_RING_SIZE_DEFAULT ; 
 int /*<<< orphan*/  AG71XX_TX_RING_SPLIT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_5__*) ; 
 int /*<<< orphan*/  ag71xx_debugfs_exit (struct ag71xx*) ; 
 int ag71xx_debugfs_init (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_dump_regs (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_ethtool_ops ; 
 int /*<<< orphan*/  ag71xx_hw_init (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_interrupt ; 
 int /*<<< orphan*/  ag71xx_msg_level ; 
 int /*<<< orphan*/  ag71xx_netdev_ops ; 
 int /*<<< orphan*/  ag71xx_oom_timer_handler ; 
 int ag71xx_phy_connect (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_phy_disconnect (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_poll ; 
 int /*<<< orphan*/  ag71xx_restart_work_func ; 
 void* ag71xx_ring_size_order (int) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_5__*) ; 
 struct net_device* devm_alloc_etherdev (TYPE_5__*,int) ; 
 scalar_t__ devm_ioremap_nocache (TYPE_5__*,scalar_t__,scalar_t__) ; 
 int devm_request_irq (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct net_device*) ; 
 TYPE_4__* dmam_alloc_coherent (TYPE_5__*,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ag71xx* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_msg_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_modes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ag71xx_probe(struct platform_device *pdev)
{
	struct net_device *dev;
	struct resource *res;
	struct ag71xx *ag;
	struct ag71xx_platform_data *pdata;
	int tx_size, err;

	pdata = pdev->dev.platform_data;
	if (!pdata) {
		dev_err(&pdev->dev, "no platform data specified\n");
		return -ENXIO;

	}

	if (pdata->mii_bus_dev == NULL && pdata->phy_mask) {
		dev_err(&pdev->dev, "no MII bus device specified\n");
		return -EINVAL;
	}

	dev = devm_alloc_etherdev(&pdev->dev, sizeof(*ag));
	if (!dev)
		return -ENOMEM;

	if (!pdata->max_frame_len || !pdata->desc_pktlen_mask)
		return -EINVAL;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -EINVAL;

	SET_NETDEV_DEV(dev, &pdev->dev);

	ag = netdev_priv(dev);
	ag->pdev = pdev;
	ag->dev = dev;
	ag->msg_enable = netif_msg_init(ag71xx_msg_level,
					AG71XX_DEFAULT_MSG_ENABLE);
	spin_lock_init(&ag->lock);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "mac_base");
	if (!res) {
		dev_err(&pdev->dev, "no mac_base resource found\n");
		return -ENXIO;
	}

	ag->mac_base = devm_ioremap_nocache(&pdev->dev, res->start,
					    res->end - res->start + 1);
	if (!ag->mac_base)
		return -ENOMEM;

	dev->irq = platform_get_irq(pdev, 0);
	err = devm_request_irq(&pdev->dev, dev->irq, ag71xx_interrupt,
			       0x0, dev_name(&pdev->dev), dev);
	if (err) {
		dev_err(&pdev->dev, "unable to request IRQ %d\n", dev->irq);
		return err;
	}

	dev->base_addr = (unsigned long)ag->mac_base;
	dev->netdev_ops = &ag71xx_netdev_ops;
	dev->ethtool_ops = &ag71xx_ethtool_ops;

	INIT_DELAYED_WORK(&ag->restart_work, ag71xx_restart_work_func);

	init_timer(&ag->oom_timer);
	ag->oom_timer.data = (unsigned long) dev;
	ag->oom_timer.function = ag71xx_oom_timer_handler;

	tx_size = AG71XX_TX_RING_SIZE_DEFAULT;
	ag->rx_ring.order = ag71xx_ring_size_order(AG71XX_RX_RING_SIZE_DEFAULT);

	ag->max_frame_len = pdata->max_frame_len;
	ag->desc_pktlen_mask = pdata->desc_pktlen_mask;

	if (!pdata->is_ar724x && !pdata->is_ar91xx) {
		ag->tx_ring.desc_split = AG71XX_TX_RING_SPLIT;
		tx_size *= AG71XX_TX_RING_DS_PER_PKT;
	}
	ag->tx_ring.order = ag71xx_ring_size_order(tx_size);

	ag->stop_desc = dmam_alloc_coherent(&pdev->dev,
					sizeof(struct ag71xx_desc),
					&ag->stop_desc_dma, GFP_KERNEL);

	if (!ag->stop_desc)
		return -ENOMEM;

	ag->stop_desc->data = 0;
	ag->stop_desc->ctrl = 0;
	ag->stop_desc->next = (u32) ag->stop_desc_dma;

	memcpy(dev->dev_addr, pdata->mac_addr, ETH_ALEN);

	netif_napi_add(dev, &ag->napi, ag71xx_poll, AG71XX_NAPI_WEIGHT);

	ag71xx_dump_regs(ag);

	ag71xx_wr(ag, AG71XX_REG_MAC_CFG1, 0);

	ag71xx_hw_init(ag);

	ag71xx_dump_regs(ag);

	err = ag71xx_phy_connect(ag);
	if (err)
		return err;

	err = ag71xx_debugfs_init(ag);
	if (err)
		goto err_phy_disconnect;

	platform_set_drvdata(pdev, dev);

	err = register_netdev(dev);
	if (err) {
		dev_err(&pdev->dev, "unable to register net device\n");
		platform_set_drvdata(pdev, NULL);
		ag71xx_debugfs_exit(ag);
		goto err_phy_disconnect;
	}

	pr_info("%s: Atheros AG71xx at 0x%08lx, irq %d, mode: %s\n",
		dev->name, (unsigned long) ag->mac_base, dev->irq,
		phy_modes(pdata->phy_if_mode));

	return 0;

err_phy_disconnect:
	ag71xx_phy_disconnect(ag);
	return err;
}