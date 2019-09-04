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
struct ipr_sglist {int /*<<< orphan*/  num_dma_sg; int /*<<< orphan*/  num_sg; int /*<<< orphan*/  scatterlist; } ;
struct ipr_ioa_cfg {TYPE_2__* host; struct ipr_sglist* ucode_sglist; scalar_t__ in_reset_reload; int /*<<< orphan*/  reset_wait_q; TYPE_1__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EIO ; 
 int /*<<< orphan*/  IPR_SHUTDOWN_NORMAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipr_initiate_ioa_reset (struct ipr_ioa_cfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ipr_update_ioa_ucode(struct ipr_ioa_cfg *ioa_cfg,
				struct ipr_sglist *sglist)
{
	unsigned long lock_flags;

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	while (ioa_cfg->in_reset_reload) {
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		wait_event(ioa_cfg->reset_wait_q, !ioa_cfg->in_reset_reload);
		spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	}

	if (ioa_cfg->ucode_sglist) {
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		dev_err(&ioa_cfg->pdev->dev,
			"Microcode download already in progress\n");
		return -EIO;
	}

	sglist->num_dma_sg = dma_map_sg(&ioa_cfg->pdev->dev,
					sglist->scatterlist, sglist->num_sg,
					DMA_TO_DEVICE);

	if (!sglist->num_dma_sg) {
		spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
		dev_err(&ioa_cfg->pdev->dev,
			"Failed to map microcode download buffer!\n");
		return -EIO;
	}

	ioa_cfg->ucode_sglist = sglist;
	ipr_initiate_ioa_reset(ioa_cfg, IPR_SHUTDOWN_NORMAL);
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	wait_event(ioa_cfg->reset_wait_q, !ioa_cfg->in_reset_reload);

	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);
	ioa_cfg->ucode_sglist = NULL;
	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	return 0;
}