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
struct ipr_ioa_cfg {int msi_received; TYPE_2__* host; int /*<<< orphan*/  msi_wait_q; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ipr_test_intr(int irq, void *devp)
{
	struct ipr_ioa_cfg *ioa_cfg = (struct ipr_ioa_cfg *)devp;
	unsigned long lock_flags = 0;
	irqreturn_t rc = IRQ_HANDLED;

	dev_info(&ioa_cfg->pdev->dev, "Received IRQ : %d\n", irq);
	spin_lock_irqsave(ioa_cfg->host->host_lock, lock_flags);

	ioa_cfg->msi_received = 1;
	wake_up(&ioa_cfg->msi_wait_q);

	spin_unlock_irqrestore(ioa_cfg->host->host_lock, lock_flags);
	return rc;
}