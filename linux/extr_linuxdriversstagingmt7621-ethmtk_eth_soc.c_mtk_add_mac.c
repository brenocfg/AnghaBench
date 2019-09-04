#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct mtk_mac {int id; TYPE_8__* hw_stats; int /*<<< orphan*/  pending_work; struct device_node* of_node; struct mtk_eth* hw; } ;
struct mtk_eth {TYPE_2__** netdev; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; TYPE_1__* soc; scalar_t__ base; struct mtk_mac** mac; } ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_13__ {int reg_offset; int /*<<< orphan*/  stats_lock; } ;
struct TYPE_12__ {unsigned long base_addr; int vlan_features; int features; int /*<<< orphan*/  irq; int /*<<< orphan*/ * netdev_ops; } ;
struct TYPE_11__ {int mac_count; int hw_features; int /*<<< orphan*/  (* init_data ) (TYPE_1__*,TYPE_2__*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t MTK_REG_MTK_COUNTER_BASE ; 
 size_t MTK_REG_MTK_DMA_VID_BASE ; 
 int MTK_STAT_OFFSET ; 
 int NETIF_F_HW_VLAN_CTAG_FILTER ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int NETIF_F_HW_VLAN_CTAG_TX ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* alloc_etherdev (int) ; 
 int be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_8__* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (TYPE_2__*) ; 
 int /*<<< orphan*/  mtk_netdev_ops ; 
 int /*<<< orphan*/  mtk_pending_work ; 
 scalar_t__* mtk_reg_table ; 
 int /*<<< orphan*/  mtk_set_ethtool_ops (TYPE_2__*) ; 
 struct mtk_mac* netdev_priv (TYPE_2__*) ; 
 int /*<<< orphan*/  netif_info (struct mtk_eth*,int /*<<< orphan*/ ,TYPE_2__*,char*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  probe ; 
 int register_netdev (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int mtk_add_mac(struct mtk_eth *eth, struct device_node *np)
{
	struct mtk_mac *mac;
	const __be32 *_id = of_get_property(np, "reg", NULL);
	int id, err;

	if (!_id) {
		dev_err(eth->dev, "missing mac id\n");
		return -EINVAL;
	}
	id = be32_to_cpup(_id);
	if (id >= eth->soc->mac_count || eth->netdev[id]) {
		dev_err(eth->dev, "%d is not a valid mac id\n", id);
		return -EINVAL;
	}

	eth->netdev[id] = alloc_etherdev(sizeof(*mac));
	if (!eth->netdev[id]) {
		dev_err(eth->dev, "alloc_etherdev failed\n");
		return -ENOMEM;
	}
	mac = netdev_priv(eth->netdev[id]);
	eth->mac[id] = mac;
	mac->id = id;
	mac->hw = eth;
	mac->of_node = np;
	INIT_WORK(&mac->pending_work, mtk_pending_work);

	if (mtk_reg_table[MTK_REG_MTK_COUNTER_BASE]) {
		mac->hw_stats = devm_kzalloc(eth->dev,
					     sizeof(*mac->hw_stats),
					     GFP_KERNEL);
		if (!mac->hw_stats) {
			err = -ENOMEM;
			goto free_netdev;
		}
		spin_lock_init(&mac->hw_stats->stats_lock);
		mac->hw_stats->reg_offset = id * MTK_STAT_OFFSET;
	}

	SET_NETDEV_DEV(eth->netdev[id], eth->dev);
	eth->netdev[id]->netdev_ops = &mtk_netdev_ops;
	eth->netdev[id]->base_addr = (unsigned long)eth->base;

	if (eth->soc->init_data)
		eth->soc->init_data(eth->soc, eth->netdev[id]);

	eth->netdev[id]->vlan_features = eth->soc->hw_features &
		~(NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX);
	eth->netdev[id]->features |= eth->soc->hw_features;

	if (mtk_reg_table[MTK_REG_MTK_DMA_VID_BASE])
		eth->netdev[id]->features |= NETIF_F_HW_VLAN_CTAG_FILTER;

	mtk_set_ethtool_ops(eth->netdev[id]);

	err = register_netdev(eth->netdev[id]);
	if (err) {
		dev_err(eth->dev, "error bringing up device\n");
		err = -ENOMEM;
		goto free_netdev;
	}
	eth->netdev[id]->irq = eth->irq;
	netif_info(eth, probe, eth->netdev[id],
		   "mediatek frame engine at 0x%08lx, irq %d\n",
		   eth->netdev[id]->base_addr, eth->netdev[id]->irq);

	return 0;

free_netdev:
	free_netdev(eth->netdev[id]);
	return err;
}