#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mvumi_hba {int global_isr; int isr_status; scalar_t__ fw_state; TYPE_4__* shost; TYPE_3__* regs; TYPE_2__* pdev; TYPE_1__* instancet; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_8__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_7__ {int int_dl_cpu2pciea; int int_comaout; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ (* clear_intr ) (struct mvumi_hba*) ;} ;

/* Variables and functions */
 int DRBL_BUS_CHANGE ; 
 int DRBL_EVENT_NOTIFY ; 
 int DRBL_HANDSHAKE_ISR ; 
 scalar_t__ FW_STATE_STARTED ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mvumi_handle_clob (struct mvumi_hba*) ; 
 int /*<<< orphan*/  mvumi_handshake (struct mvumi_hba*) ; 
 int /*<<< orphan*/  mvumi_launch_events (struct mvumi_hba*,int) ; 
 int /*<<< orphan*/  mvumi_receive_ob_list_entry (struct mvumi_hba*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ stub1 (struct mvumi_hba*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t mvumi_isr_handler(int irq, void *devp)
{
	struct mvumi_hba *mhba = (struct mvumi_hba *) devp;
	unsigned long flags;

	spin_lock_irqsave(mhba->shost->host_lock, flags);
	if (unlikely(mhba->instancet->clear_intr(mhba) || !mhba->global_isr)) {
		spin_unlock_irqrestore(mhba->shost->host_lock, flags);
		return IRQ_NONE;
	}

	if (mhba->global_isr & mhba->regs->int_dl_cpu2pciea) {
		if (mhba->isr_status & (DRBL_BUS_CHANGE | DRBL_EVENT_NOTIFY))
			mvumi_launch_events(mhba, mhba->isr_status);
		if (mhba->isr_status & DRBL_HANDSHAKE_ISR) {
			dev_warn(&mhba->pdev->dev, "enter handshake again!\n");
			mvumi_handshake(mhba);
		}

	}

	if (mhba->global_isr & mhba->regs->int_comaout)
		mvumi_receive_ob_list_entry(mhba);

	mhba->global_isr = 0;
	mhba->isr_status = 0;
	if (mhba->fw_state == FW_STATE_STARTED)
		mvumi_handle_clob(mhba);
	spin_unlock_irqrestore(mhba->shost->host_lock, flags);
	return IRQ_HANDLED;
}