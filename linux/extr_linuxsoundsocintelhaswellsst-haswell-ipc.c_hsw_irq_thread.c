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
typedef  int u32 ;
struct sst_generic_ipc {int /*<<< orphan*/  kwork; } ;
struct sst_hsw {int /*<<< orphan*/  dsp; struct sst_generic_ipc ipc; } ;
struct sst_dsp {int /*<<< orphan*/  spinlock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SST_IMRX ; 
 int SST_IMRX_BUSY ; 
 int SST_IMRX_DONE ; 
 int /*<<< orphan*/  SST_IPCD ; 
 int SST_IPCD_BUSY ; 
 int SST_IPCD_DONE ; 
 int /*<<< orphan*/  SST_IPCX ; 
 int SST_IPCX_DONE ; 
 int /*<<< orphan*/  hsw_process_notification (struct sst_hsw*) ; 
 int /*<<< orphan*/  hsw_process_reply (struct sst_hsw*,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct sst_hsw* sst_dsp_get_thread_context (struct sst_dsp*) ; 
 int sst_dsp_ipc_msg_rx (int /*<<< orphan*/ ) ; 
 int sst_dsp_shim_read_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t hsw_irq_thread(int irq, void *context)
{
	struct sst_dsp *sst = (struct sst_dsp *) context;
	struct sst_hsw *hsw = sst_dsp_get_thread_context(sst);
	struct sst_generic_ipc *ipc = &hsw->ipc;
	u32 ipcx, ipcd;
	unsigned long flags;

	spin_lock_irqsave(&sst->spinlock, flags);

	ipcx = sst_dsp_ipc_msg_rx(hsw->dsp);
	ipcd = sst_dsp_shim_read_unlocked(sst, SST_IPCD);

	/* reply message from DSP */
	if (ipcx & SST_IPCX_DONE) {

		/* Handle Immediate reply from DSP Core */
		hsw_process_reply(hsw, ipcx);

		/* clear DONE bit - tell DSP we have completed */
		sst_dsp_shim_update_bits_unlocked(sst, SST_IPCX,
			SST_IPCX_DONE, 0);

		/* unmask Done interrupt */
		sst_dsp_shim_update_bits_unlocked(sst, SST_IMRX,
			SST_IMRX_DONE, 0);
	}

	/* new message from DSP */
	if (ipcd & SST_IPCD_BUSY) {

		/* Handle Notification and Delayed reply from DSP Core */
		hsw_process_notification(hsw);

		/* clear BUSY bit and set DONE bit - accept new messages */
		sst_dsp_shim_update_bits_unlocked(sst, SST_IPCD,
			SST_IPCD_BUSY | SST_IPCD_DONE, SST_IPCD_DONE);

		/* unmask busy interrupt */
		sst_dsp_shim_update_bits_unlocked(sst, SST_IMRX,
			SST_IMRX_BUSY, 0);
	}

	spin_unlock_irqrestore(&sst->spinlock, flags);

	/* continue to send any remaining messages... */
	schedule_work(&ipc->kwork);

	return IRQ_HANDLED;
}