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
struct TYPE_5__ {int done; scalar_t__ busy; } ;
struct TYPE_6__ {TYPE_1__ part; } ;
struct TYPE_7__ {int /*<<< orphan*/  header_low_payload; TYPE_2__ header_high; } ;
union ipc_header_mrfld {void* full; TYPE_3__ p; } ;
struct TYPE_8__ {int busy_interrupt; } ;
union interrupt_reg_mrfld {void* full; TYPE_4__ part; } ;
struct intel_sst_drv {int /*<<< orphan*/  ipc_spin_lock; int /*<<< orphan*/  shim; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_ACK_SUCCESS ; 
 int /*<<< orphan*/  SST_IMRX ; 
 int /*<<< orphan*/  SST_IPCD ; 
 int /*<<< orphan*/  SST_ISRX ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 void* sst_shim_read64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_shim_write64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

void intel_sst_clear_intr_mrfld(struct intel_sst_drv *sst_drv_ctx)
{
	union interrupt_reg_mrfld isr;
	union interrupt_reg_mrfld imr;
	union ipc_header_mrfld clear_ipc;
	unsigned long irq_flags;

	spin_lock_irqsave(&sst_drv_ctx->ipc_spin_lock, irq_flags);
	imr.full = sst_shim_read64(sst_drv_ctx->shim, SST_IMRX);
	isr.full = sst_shim_read64(sst_drv_ctx->shim, SST_ISRX);

	/* write 1 to clear*/
	isr.part.busy_interrupt = 1;
	sst_shim_write64(sst_drv_ctx->shim, SST_ISRX, isr.full);

	/* Set IA done bit */
	clear_ipc.full = sst_shim_read64(sst_drv_ctx->shim, SST_IPCD);

	clear_ipc.p.header_high.part.busy = 0;
	clear_ipc.p.header_high.part.done = 1;
	clear_ipc.p.header_low_payload = IPC_ACK_SUCCESS;
	sst_shim_write64(sst_drv_ctx->shim, SST_IPCD, clear_ipc.full);
	/* un mask busy interrupt */
	imr.part.busy_interrupt = 0;
	sst_shim_write64(sst_drv_ctx->shim, SST_IMRX, imr.full);
	spin_unlock_irqrestore(&sst_drv_ctx->ipc_spin_lock, irq_flags);
}