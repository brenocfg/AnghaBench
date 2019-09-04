#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sh_eth_private {int port; int /*<<< orphan*/  napi; struct sh_eth_cpu_data* cd; int /*<<< orphan*/  tsu_addr; int /*<<< orphan*/  msg_enable; int /*<<< orphan*/  reg_offset; int /*<<< orphan*/  ether_link_active_low; int /*<<< orphan*/  no_ether_link; int /*<<< orphan*/  phy_interface; int /*<<< orphan*/  phy_id; struct platform_device* pdev; int /*<<< orphan*/  lock; int /*<<< orphan*/  addr; int /*<<< orphan*/  num_rx_ring; int /*<<< orphan*/  num_tx_ring; } ;
struct sh_eth_plat_data {int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  ether_link_active_low; int /*<<< orphan*/  no_ether_link; int /*<<< orphan*/  phy_interface; int /*<<< orphan*/  phy; } ;
struct sh_eth_cpu_data {int register_type; scalar_t__ magic; scalar_t__ rmiimode; int /*<<< orphan*/  (* chip_reset ) (struct net_device*) ;scalar_t__ tsu; } ;
struct resource {scalar_t__ start; } ;
struct platform_device_id {scalar_t__ driver_data; } ;
struct TYPE_16__ {scalar_t__ of_node; } ;
struct platform_device {int id; TYPE_1__ dev; } ;
struct net_device {int irq; int /*<<< orphan*/  dev_addr; scalar_t__ base_addr; int /*<<< orphan*/  features; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  min_mtu; scalar_t__ max_mtu; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 scalar_t__ ETH_FCS_LEN ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_MIN_MTU ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RMIIMODE ; 
 int /*<<< orphan*/  RX_RING_SIZE ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  SH_ETH_DEF_MSG_ENABLE ; 
 int /*<<< orphan*/  TX_RING_SIZE ; 
 int /*<<< orphan*/  TX_TIMEOUT ; 
 scalar_t__ VLAN_HLEN ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct sh_eth_plat_data* dev_get_platdata (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  device_set_wakeup_capable (TYPE_1__*,int) ; 
 int /*<<< orphan*/  devm_ioremap (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 int /*<<< orphan*/  devm_request_mem_region (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sh_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_get_match_data (TYPE_1__*) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct net_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_put (TYPE_1__*) ; 
 int /*<<< orphan*/  read_mac_address (struct net_device*,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  sh_eth_ethtool_ops ; 
 int /*<<< orphan*/  sh_eth_get_register_offset (int) ; 
 int /*<<< orphan*/  sh_eth_netdev_ops ; 
 int /*<<< orphan*/  sh_eth_netdev_ops_tsu ; 
 struct sh_eth_plat_data* sh_eth_parse_dt (TYPE_1__*) ; 
 int /*<<< orphan*/  sh_eth_poll ; 
 int /*<<< orphan*/  sh_eth_set_default_cpu_data (struct sh_eth_cpu_data*) ; 
 int /*<<< orphan*/  sh_eth_tsu_init (struct sh_eth_private*) ; 
 int /*<<< orphan*/  sh_eth_write (struct net_device*,int,int /*<<< orphan*/ ) ; 
 int sh_mdio_init (struct sh_eth_private*,struct sh_eth_plat_data*) ; 
 int /*<<< orphan*/  sh_mdio_release (struct sh_eth_private*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

__attribute__((used)) static int sh_eth_drv_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct sh_eth_plat_data *pd = dev_get_platdata(&pdev->dev);
	const struct platform_device_id *id = platform_get_device_id(pdev);
	struct sh_eth_private *mdp;
	struct net_device *ndev;
	int ret;

	/* get base addr */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	ndev = alloc_etherdev(sizeof(struct sh_eth_private));
	if (!ndev)
		return -ENOMEM;

	pm_runtime_enable(&pdev->dev);
	pm_runtime_get_sync(&pdev->dev);

	ret = platform_get_irq(pdev, 0);
	if (ret < 0)
		goto out_release;
	ndev->irq = ret;

	SET_NETDEV_DEV(ndev, &pdev->dev);

	mdp = netdev_priv(ndev);
	mdp->num_tx_ring = TX_RING_SIZE;
	mdp->num_rx_ring = RX_RING_SIZE;
	mdp->addr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mdp->addr)) {
		ret = PTR_ERR(mdp->addr);
		goto out_release;
	}

	ndev->base_addr = res->start;

	spin_lock_init(&mdp->lock);
	mdp->pdev = pdev;

	if (pdev->dev.of_node)
		pd = sh_eth_parse_dt(&pdev->dev);
	if (!pd) {
		dev_err(&pdev->dev, "no platform data\n");
		ret = -EINVAL;
		goto out_release;
	}

	/* get PHY ID */
	mdp->phy_id = pd->phy;
	mdp->phy_interface = pd->phy_interface;
	mdp->no_ether_link = pd->no_ether_link;
	mdp->ether_link_active_low = pd->ether_link_active_low;

	/* set cpu data */
	if (id)
		mdp->cd = (struct sh_eth_cpu_data *)id->driver_data;
	else
		mdp->cd = (struct sh_eth_cpu_data *)of_device_get_match_data(&pdev->dev);

	mdp->reg_offset = sh_eth_get_register_offset(mdp->cd->register_type);
	if (!mdp->reg_offset) {
		dev_err(&pdev->dev, "Unknown register type (%d)\n",
			mdp->cd->register_type);
		ret = -EINVAL;
		goto out_release;
	}
	sh_eth_set_default_cpu_data(mdp->cd);

	/* User's manual states max MTU should be 2048 but due to the
	 * alignment calculations in sh_eth_ring_init() the practical
	 * MTU is a bit less. Maybe this can be optimized some more.
	 */
	ndev->max_mtu = 2000 - (ETH_HLEN + VLAN_HLEN + ETH_FCS_LEN);
	ndev->min_mtu = ETH_MIN_MTU;

	/* set function */
	if (mdp->cd->tsu)
		ndev->netdev_ops = &sh_eth_netdev_ops_tsu;
	else
		ndev->netdev_ops = &sh_eth_netdev_ops;
	ndev->ethtool_ops = &sh_eth_ethtool_ops;
	ndev->watchdog_timeo = TX_TIMEOUT;

	/* debug message level */
	mdp->msg_enable = SH_ETH_DEF_MSG_ENABLE;

	/* read and set MAC address */
	read_mac_address(ndev, pd->mac_addr);
	if (!is_valid_ether_addr(ndev->dev_addr)) {
		dev_warn(&pdev->dev,
			 "no valid MAC address supplied, using a random one.\n");
		eth_hw_addr_random(ndev);
	}

	if (mdp->cd->tsu) {
		int port = pdev->id < 0 ? 0 : pdev->id % 2;
		struct resource *rtsu;

		rtsu = platform_get_resource(pdev, IORESOURCE_MEM, 1);
		if (!rtsu) {
			dev_err(&pdev->dev, "no TSU resource\n");
			ret = -ENODEV;
			goto out_release;
		}
		/* We can only request the  TSU region  for the first port
		 * of the two  sharing this TSU for the probe to succeed...
		 */
		if (port == 0 &&
		    !devm_request_mem_region(&pdev->dev, rtsu->start,
					     resource_size(rtsu),
					     dev_name(&pdev->dev))) {
			dev_err(&pdev->dev, "can't request TSU resource.\n");
			ret = -EBUSY;
			goto out_release;
		}
		/* ioremap the TSU registers */
		mdp->tsu_addr = devm_ioremap(&pdev->dev, rtsu->start,
					     resource_size(rtsu));
		if (!mdp->tsu_addr) {
			dev_err(&pdev->dev, "TSU region ioremap() failed.\n");
			ret = -ENOMEM;
			goto out_release;
		}
		mdp->port = port;
		ndev->features = NETIF_F_HW_VLAN_CTAG_FILTER;

		/* Need to init only the first port of the two sharing a TSU */
		if (port == 0) {
			if (mdp->cd->chip_reset)
				mdp->cd->chip_reset(ndev);

			/* TSU init (Init only)*/
			sh_eth_tsu_init(mdp);
		}
	}

	if (mdp->cd->rmiimode)
		sh_eth_write(ndev, 0x1, RMIIMODE);

	/* MDIO bus init */
	ret = sh_mdio_init(mdp, pd);
	if (ret) {
		if (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "MDIO init failed: %d\n", ret);
		goto out_release;
	}

	netif_napi_add(ndev, &mdp->napi, sh_eth_poll, 64);

	/* network device register */
	ret = register_netdev(ndev);
	if (ret)
		goto out_napi_del;

	if (mdp->cd->magic)
		device_set_wakeup_capable(&pdev->dev, 1);

	/* print device information */
	netdev_info(ndev, "Base address at 0x%x, %pM, IRQ %d.\n",
		    (u32)ndev->base_addr, ndev->dev_addr, ndev->irq);

	pm_runtime_put(&pdev->dev);
	platform_set_drvdata(pdev, ndev);

	return ret;

out_napi_del:
	netif_napi_del(&mdp->napi);
	sh_mdio_release(mdp);

out_release:
	/* net_dev free */
	free_netdev(ndev);

	pm_runtime_put(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	return ret;
}