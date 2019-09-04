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
typedef  int /*<<< orphan*/  u8 ;
typedef  void* u32 ;
struct netcp_intf {void* rx_channel; int /*<<< orphan*/  ndev_dev; int /*<<< orphan*/  dma_chan_name; TYPE_3__* netcp_device; void** rx_fdq; void* rx_queue_id; scalar_t__* rx_queue_depths; void* rx_queue; void* tx_compl_q; void* tx_compl_qid; void* tx_pool; int /*<<< orphan*/  tx_pool_region_id; int /*<<< orphan*/  tx_pool_size; void* rx_pool; int /*<<< orphan*/  rx_pool_region_id; int /*<<< orphan*/  rx_pool_size; } ;
struct net_device {char* name; } ;
struct knav_queue_notify_config {struct netcp_intf* fn_arg; int /*<<< orphan*/  fn; } ;
struct TYPE_4__ {int einfo_present; int psinfo_present; int psinfo_at_sop; void** fdq; int /*<<< orphan*/  thresh; void* dst_q; int /*<<< orphan*/  sop_offset; int /*<<< orphan*/  desc_type; int /*<<< orphan*/  err_mode; } ;
struct TYPE_5__ {TYPE_1__ rx; } ;
struct knav_dma_cfg {TYPE_2__ u; int /*<<< orphan*/  direction; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DESC_HOST ; 
 int /*<<< orphan*/  DMA_DEV_TO_MEM ; 
 int /*<<< orphan*/  DMA_DROP ; 
 int /*<<< orphan*/  DMA_THRESH_NONE ; 
 scalar_t__ IS_ERR (void*) ; 
 scalar_t__ IS_ERR_OR_NULL (void*) ; 
 int KNAV_DMA_FDQ_PER_CHAN ; 
 void* KNAV_QUEUE_GP ; 
 int /*<<< orphan*/  KNAV_QUEUE_SET_NOTIFIER ; 
 int /*<<< orphan*/  NETCP_SOP_OFFSET ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 void* knav_dma_open_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct knav_dma_cfg*) ; 
 void* knav_pool_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int knav_queue_device_control (void*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  knav_queue_disable_notify (void*) ; 
 void* knav_queue_get_id (void*) ; 
 void* knav_queue_open (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct knav_dma_cfg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netcp_free_navigator_resources (struct netcp_intf*) ; 
 int /*<<< orphan*/  netcp_rx_notify ; 
 int /*<<< orphan*/  netcp_tx_notify ; 
 struct netcp_intf* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,char*,...) ; 

__attribute__((used)) static int netcp_setup_navigator_resources(struct net_device *ndev)
{
	struct netcp_intf *netcp = netdev_priv(ndev);
	struct knav_queue_notify_config notify_cfg;
	struct knav_dma_cfg config;
	u32 last_fdq = 0;
	u8 name[16];
	int ret;
	int i;

	/* Create Rx/Tx descriptor pools */
	snprintf(name, sizeof(name), "rx-pool-%s", ndev->name);
	netcp->rx_pool = knav_pool_create(name, netcp->rx_pool_size,
						netcp->rx_pool_region_id);
	if (IS_ERR_OR_NULL(netcp->rx_pool)) {
		dev_err(netcp->ndev_dev, "Couldn't create rx pool\n");
		ret = PTR_ERR(netcp->rx_pool);
		goto fail;
	}

	snprintf(name, sizeof(name), "tx-pool-%s", ndev->name);
	netcp->tx_pool = knav_pool_create(name, netcp->tx_pool_size,
						netcp->tx_pool_region_id);
	if (IS_ERR_OR_NULL(netcp->tx_pool)) {
		dev_err(netcp->ndev_dev, "Couldn't create tx pool\n");
		ret = PTR_ERR(netcp->tx_pool);
		goto fail;
	}

	/* open Tx completion queue */
	snprintf(name, sizeof(name), "tx-compl-%s", ndev->name);
	netcp->tx_compl_q = knav_queue_open(name, netcp->tx_compl_qid, 0);
	if (IS_ERR(netcp->tx_compl_q)) {
		ret = PTR_ERR(netcp->tx_compl_q);
		goto fail;
	}
	netcp->tx_compl_qid = knav_queue_get_id(netcp->tx_compl_q);

	/* Set notification for Tx completion */
	notify_cfg.fn = netcp_tx_notify;
	notify_cfg.fn_arg = netcp;
	ret = knav_queue_device_control(netcp->tx_compl_q,
					KNAV_QUEUE_SET_NOTIFIER,
					(unsigned long)&notify_cfg);
	if (ret)
		goto fail;

	knav_queue_disable_notify(netcp->tx_compl_q);

	/* open Rx completion queue */
	snprintf(name, sizeof(name), "rx-compl-%s", ndev->name);
	netcp->rx_queue = knav_queue_open(name, netcp->rx_queue_id, 0);
	if (IS_ERR(netcp->rx_queue)) {
		ret = PTR_ERR(netcp->rx_queue);
		goto fail;
	}
	netcp->rx_queue_id = knav_queue_get_id(netcp->rx_queue);

	/* Set notification for Rx completion */
	notify_cfg.fn = netcp_rx_notify;
	notify_cfg.fn_arg = netcp;
	ret = knav_queue_device_control(netcp->rx_queue,
					KNAV_QUEUE_SET_NOTIFIER,
					(unsigned long)&notify_cfg);
	if (ret)
		goto fail;

	knav_queue_disable_notify(netcp->rx_queue);

	/* open Rx FDQs */
	for (i = 0; i < KNAV_DMA_FDQ_PER_CHAN && netcp->rx_queue_depths[i];
	     ++i) {
		snprintf(name, sizeof(name), "rx-fdq-%s-%d", ndev->name, i);
		netcp->rx_fdq[i] = knav_queue_open(name, KNAV_QUEUE_GP, 0);
		if (IS_ERR(netcp->rx_fdq[i])) {
			ret = PTR_ERR(netcp->rx_fdq[i]);
			goto fail;
		}
	}

	memset(&config, 0, sizeof(config));
	config.direction		= DMA_DEV_TO_MEM;
	config.u.rx.einfo_present	= true;
	config.u.rx.psinfo_present	= true;
	config.u.rx.err_mode		= DMA_DROP;
	config.u.rx.desc_type		= DMA_DESC_HOST;
	config.u.rx.psinfo_at_sop	= false;
	config.u.rx.sop_offset		= NETCP_SOP_OFFSET;
	config.u.rx.dst_q		= netcp->rx_queue_id;
	config.u.rx.thresh		= DMA_THRESH_NONE;

	for (i = 0; i < KNAV_DMA_FDQ_PER_CHAN; ++i) {
		if (netcp->rx_fdq[i])
			last_fdq = knav_queue_get_id(netcp->rx_fdq[i]);
		config.u.rx.fdq[i] = last_fdq;
	}

	netcp->rx_channel = knav_dma_open_channel(netcp->netcp_device->device,
					netcp->dma_chan_name, &config);
	if (IS_ERR(netcp->rx_channel)) {
		dev_err(netcp->ndev_dev, "failed opening rx chan(%s\n",
			netcp->dma_chan_name);
		ret = PTR_ERR(netcp->rx_channel);
		goto fail;
	}

	dev_dbg(netcp->ndev_dev, "opened RX channel: %p\n", netcp->rx_channel);
	return 0;

fail:
	netcp_free_navigator_resources(netcp);
	return ret;
}