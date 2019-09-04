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
struct TYPE_3__ {struct device* parent; } ;
struct rproc {int /*<<< orphan*/  bootaddr; TYPE_1__ dev; struct omap_rproc* priv; } ;
struct TYPE_4__ {struct omap_rproc_pdata* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct omap_rproc_pdata {int (* device_enable ) (struct platform_device*) ;int /*<<< orphan*/  mbox_name; int /*<<< orphan*/  (* set_bootaddr ) (int /*<<< orphan*/ ) ;} ;
struct mbox_client {int tx_block; int knows_txdone; int /*<<< orphan*/  rx_callback; int /*<<< orphan*/ * tx_done; struct device* dev; } ;
struct omap_rproc {int /*<<< orphan*/  mbox; struct mbox_client client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ RP_MBOX_ECHO_REQUEST ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 
 int mbox_send_message (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  omap_mbox_request_channel (struct mbox_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_rproc_mbox_callback ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (struct platform_device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int omap_rproc_start(struct rproc *rproc)
{
	struct omap_rproc *oproc = rproc->priv;
	struct device *dev = rproc->dev.parent;
	struct platform_device *pdev = to_platform_device(dev);
	struct omap_rproc_pdata *pdata = pdev->dev.platform_data;
	int ret;
	struct mbox_client *client = &oproc->client;

	if (pdata->set_bootaddr)
		pdata->set_bootaddr(rproc->bootaddr);

	client->dev = dev;
	client->tx_done = NULL;
	client->rx_callback = omap_rproc_mbox_callback;
	client->tx_block = false;
	client->knows_txdone = false;

	oproc->mbox = omap_mbox_request_channel(client, pdata->mbox_name);
	if (IS_ERR(oproc->mbox)) {
		ret = -EBUSY;
		dev_err(dev, "mbox_request_channel failed: %ld\n",
			PTR_ERR(oproc->mbox));
		return ret;
	}

	/*
	 * Ping the remote processor. this is only for sanity-sake;
	 * there is no functional effect whatsoever.
	 *
	 * Note that the reply will _not_ arrive immediately: this message
	 * will wait in the mailbox fifo until the remote processor is booted.
	 */
	ret = mbox_send_message(oproc->mbox, (void *)RP_MBOX_ECHO_REQUEST);
	if (ret < 0) {
		dev_err(dev, "mbox_send_message failed: %d\n", ret);
		goto put_mbox;
	}

	ret = pdata->device_enable(pdev);
	if (ret) {
		dev_err(dev, "omap_device_enable failed: %d\n", ret);
		goto put_mbox;
	}

	return 0;

put_mbox:
	mbox_free_channel(oproc->mbox);
	return ret;
}