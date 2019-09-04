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
struct mmc_host {int dummy; } ;
struct gbphy_device {int dummy; } ;
struct gb_sdio_host {int removed; int /*<<< orphan*/  mrq_workqueue; int /*<<< orphan*/  lock; struct mmc_host* mmc; struct gb_connection* connection; } ;
struct gb_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_destroy (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable_rx (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_set_data (struct gb_connection*,int /*<<< orphan*/ *) ; 
 struct gb_sdio_host* gb_gbphy_get_data (struct gbphy_device*) ; 
 int /*<<< orphan*/  gbphy_runtime_get_noresume (struct gbphy_device*) ; 
 int gbphy_runtime_get_sync (struct gbphy_device*) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_sdio_remove(struct gbphy_device *gbphy_dev)
{
	struct gb_sdio_host *host = gb_gbphy_get_data(gbphy_dev);
	struct gb_connection *connection = host->connection;
	struct mmc_host *mmc;
	int ret;

	ret = gbphy_runtime_get_sync(gbphy_dev);
	if (ret)
		gbphy_runtime_get_noresume(gbphy_dev);

	mutex_lock(&host->lock);
	host->removed = true;
	mmc = host->mmc;
	gb_connection_set_data(connection, NULL);
	mutex_unlock(&host->lock);

	flush_workqueue(host->mrq_workqueue);
	destroy_workqueue(host->mrq_workqueue);
	gb_connection_disable_rx(connection);
	mmc_remove_host(mmc);
	gb_connection_disable(connection);
	gb_connection_destroy(connection);
	mmc_free_host(mmc);
}