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
struct mmc_host {int max_segs; int max_blk_count; int max_req_size; int max_blk_size; int max_seg_size; int /*<<< orphan*/ * ops; } ;
struct gbphy_device_id {int dummy; } ;
struct gbphy_device {int /*<<< orphan*/  dev; TYPE_1__* cport_desc; int /*<<< orphan*/  bundle; } ;
struct gb_sdio_host {int removed; int /*<<< orphan*/  mrq_workqueue; scalar_t__ queued_events; int /*<<< orphan*/  mrqwork; int /*<<< orphan*/  xfer; int /*<<< orphan*/  lock; struct mmc_host* mmc; struct gbphy_device* gbphy_dev; struct gb_connection* connection; } ;
struct gb_connection {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct gb_connection*) ; 
 int PTR_ERR (struct gb_connection*) ; 
 int _gb_sdio_process_events (struct gb_sdio_host*,scalar_t__) ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct gb_connection* gb_connection_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_destroy (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int gb_connection_enable (struct gb_connection*) ; 
 int gb_connection_enable_tx (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_set_data (struct gb_connection*,struct gb_sdio_host*) ; 
 int /*<<< orphan*/  gb_gbphy_set_data (struct gbphy_device*,struct gb_sdio_host*) ; 
 int gb_sdio_get_caps (struct gb_sdio_host*) ; 
 int /*<<< orphan*/  gb_sdio_mrq_work ; 
 int /*<<< orphan*/  gb_sdio_ops ; 
 int /*<<< orphan*/  gb_sdio_request_handler ; 
 int /*<<< orphan*/  gbphy_runtime_put_autosuspend (struct gbphy_device*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int mmc_add_host (struct mmc_host*) ; 
 struct mmc_host* mmc_alloc_host (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct gb_sdio_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_sdio_probe(struct gbphy_device *gbphy_dev,
			 const struct gbphy_device_id *id)
{
	struct gb_connection *connection;
	struct mmc_host *mmc;
	struct gb_sdio_host *host;
	int ret = 0;

	mmc = mmc_alloc_host(sizeof(*host), &gbphy_dev->dev);
	if (!mmc)
		return -ENOMEM;

	connection = gb_connection_create(gbphy_dev->bundle,
					  le16_to_cpu(gbphy_dev->cport_desc->id),
					  gb_sdio_request_handler);
	if (IS_ERR(connection)) {
		ret = PTR_ERR(connection);
		goto exit_mmc_free;
	}

	host = mmc_priv(mmc);
	host->mmc = mmc;
	host->removed = true;

	host->connection = connection;
	gb_connection_set_data(connection, host);
	host->gbphy_dev = gbphy_dev;
	gb_gbphy_set_data(gbphy_dev, host);

	ret = gb_connection_enable_tx(connection);
	if (ret)
		goto exit_connection_destroy;

	ret = gb_sdio_get_caps(host);
	if (ret < 0)
		goto exit_connection_disable;

	mmc->ops = &gb_sdio_ops;

	mmc->max_segs = host->mmc->max_blk_count;

	/* for now we make a map 1:1 between max request and segment size */
	mmc->max_req_size = mmc->max_blk_size * mmc->max_blk_count;
	mmc->max_seg_size = mmc->max_req_size;

	mutex_init(&host->lock);
	spin_lock_init(&host->xfer);
	host->mrq_workqueue = alloc_workqueue("mmc-%s", 0, 1,
					      dev_name(&gbphy_dev->dev));
	if (!host->mrq_workqueue) {
		ret = -ENOMEM;
		goto exit_connection_disable;
	}
	INIT_WORK(&host->mrqwork, gb_sdio_mrq_work);

	ret = gb_connection_enable(connection);
	if (ret)
		goto exit_wq_destroy;

	ret = mmc_add_host(mmc);
	if (ret < 0)
		goto exit_wq_destroy;
	host->removed = false;
	ret = _gb_sdio_process_events(host, host->queued_events);
	host->queued_events = 0;

	gbphy_runtime_put_autosuspend(gbphy_dev);

	return ret;

exit_wq_destroy:
	destroy_workqueue(host->mrq_workqueue);
exit_connection_disable:
	gb_connection_disable(connection);
exit_connection_destroy:
	gb_connection_destroy(connection);
exit_mmc_free:
	mmc_free_host(mmc);

	return ret;
}