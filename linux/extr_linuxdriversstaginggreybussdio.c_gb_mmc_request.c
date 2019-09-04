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
struct mmc_request {struct mmc_command* cmd; } ;
struct mmc_host {int dummy; } ;
struct mmc_command {scalar_t__ opcode; int /*<<< orphan*/  error; } ;
struct gb_sdio_host {int xfer_stop; int /*<<< orphan*/  lock; struct mmc_request* mrq; int /*<<< orphan*/  mrqwork; int /*<<< orphan*/  mrq_workqueue; int /*<<< orphan*/  card_present; scalar_t__ removed; int /*<<< orphan*/  xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEDIUM ; 
 int /*<<< orphan*/  ESHUTDOWN ; 
 scalar_t__ MMC_STOP_TRANSMISSION ; 
 int /*<<< orphan*/  WARN_ON (struct mmc_request*) ; 
 struct gb_sdio_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_request_done (struct mmc_host*,struct mmc_request*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_mmc_request(struct mmc_host *mmc, struct mmc_request *mrq)
{
	struct gb_sdio_host *host = mmc_priv(mmc);
	struct mmc_command *cmd = mrq->cmd;

	/* Check if it is a cancel to ongoing transfer */
	if (cmd->opcode == MMC_STOP_TRANSMISSION) {
		spin_lock(&host->xfer);
		host->xfer_stop = true;
		spin_unlock(&host->xfer);
	}

	mutex_lock(&host->lock);

	WARN_ON(host->mrq);
	host->mrq = mrq;

	if (host->removed) {
		mrq->cmd->error = -ESHUTDOWN;
		goto out;
	}
	if (!host->card_present) {
		mrq->cmd->error = -ENOMEDIUM;
		goto out;
	}

	queue_work(host->mrq_workqueue, &host->mrqwork);

	mutex_unlock(&host->lock);
	return;

out:
	host->mrq = NULL;
	mutex_unlock(&host->lock);
	mmc_request_done(mmc, mrq);
}