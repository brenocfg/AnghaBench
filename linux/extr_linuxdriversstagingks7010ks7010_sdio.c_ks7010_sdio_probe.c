#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sdio_func {int device; int /*<<< orphan*/  dev; int /*<<< orphan*/  vendor; int /*<<< orphan*/  class; int /*<<< orphan*/  cur_blksize; TYPE_2__* card; } ;
struct sdio_device_id {int dummy; } ;
struct net_device {int dummy; } ;
struct ks_wlan_private {int /*<<< orphan*/  net_dev; int /*<<< orphan*/  rw_dwork; int /*<<< orphan*/  wq; int /*<<< orphan*/  dev_state; } ;
struct ks_sdio_card {struct sdio_func* func; struct ks_wlan_private* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  multi_block; } ;
struct TYPE_4__ {TYPE_1__ cccr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_BOOT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS7010_IO_BLOCK_SIZE ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int) ; 
 int dev_alloc_name (struct net_device*,char*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (struct ks_sdio_card*) ; 
 int /*<<< orphan*/  ks7010_card_init (struct ks_wlan_private*) ; 
 int /*<<< orphan*/  ks7010_private_init (struct ks_wlan_private*,struct ks_sdio_card*,struct net_device*) ; 
 int /*<<< orphan*/  ks7010_rw_function ; 
 int /*<<< orphan*/  ks7010_sdio_init_irqs (struct sdio_func*,struct ks_wlan_private*) ; 
 int ks7010_sdio_setup_irqs (struct sdio_func*) ; 
 int ks7010_upload_firmware (struct ks_sdio_card*) ; 
 struct ks_sdio_card* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct ks_wlan_private* netdev_priv (struct net_device*) ; 
 int register_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 int sdio_enable_func (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_irq (struct sdio_func*) ; 
 int sdio_set_block_size (struct sdio_func*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,struct ks_sdio_card*) ; 

__attribute__((used)) static int ks7010_sdio_probe(struct sdio_func *func,
			     const struct sdio_device_id *device)
{
	struct ks_wlan_private *priv = NULL;
	struct net_device *netdev = NULL;
	struct ks_sdio_card *card;
	int ret;

	card = kzalloc(sizeof(*card), GFP_KERNEL);
	if (!card)
		return -ENOMEM;

	card->func = func;

	sdio_claim_host(func);

	ret = sdio_set_block_size(func, KS7010_IO_BLOCK_SIZE);
	if (ret)
		goto err_free_card;

	dev_dbg(&card->func->dev, "multi_block=%d sdio_set_block_size()=%d %d\n",
		func->card->cccr.multi_block, func->cur_blksize, ret);

	ret = sdio_enable_func(func);
	if (ret)
		goto err_free_card;

	ret = ks7010_sdio_setup_irqs(func);
	if (ret)
		goto err_disable_func;

	sdio_release_host(func);

	sdio_set_drvdata(func, card);

	dev_dbg(&card->func->dev, "class = 0x%X, vendor = 0x%X, device = 0x%X\n",
		func->class, func->vendor, func->device);

	/* private memory allocate */
	netdev = alloc_etherdev(sizeof(*priv));
	if (!netdev) {
		dev_err(&card->func->dev, "Unable to alloc new net device\n");
		goto err_release_irq;
	}

	ret = dev_alloc_name(netdev, "wlan%d");
	if (ret < 0) {
		dev_err(&card->func->dev, "Couldn't get name!\n");
		goto err_free_netdev;
	}

	priv = netdev_priv(netdev);

	card->priv = priv;
	SET_NETDEV_DEV(netdev, &card->func->dev);

	ks7010_private_init(priv, card, netdev);

	ret = ks7010_upload_firmware(card);
	if (ret) {
		netdev_err(priv->net_dev,
			   "firmware load failed !! ret = %d\n", ret);
		goto err_free_netdev;
	}

	ks7010_sdio_init_irqs(func, priv);

	priv->dev_state = DEVICE_STATE_BOOT;

	priv->wq = alloc_workqueue("wq", WQ_MEM_RECLAIM, 1);
	if (!priv->wq) {
		netdev_err(priv->net_dev, "create_workqueue failed !!\n");
		goto err_free_netdev;
	}

	INIT_DELAYED_WORK(&priv->rw_dwork, ks7010_rw_function);
	ks7010_card_init(priv);

	ret = register_netdev(priv->net_dev);
	if (ret)
		goto err_free_netdev;

	return 0;

 err_free_netdev:
	free_netdev(netdev);
 err_release_irq:
	sdio_claim_host(func);
	sdio_release_irq(func);
 err_disable_func:
	sdio_disable_func(func);
 err_free_card:
	sdio_release_host(func);
	sdio_set_drvdata(func, NULL);
	kfree(card);

	return -ENODEV;
}