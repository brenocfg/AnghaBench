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
typedef  int u64 ;
struct sst_generic_ipc {int /*<<< orphan*/  kwork; } ;
struct sst_dsp {int /*<<< orphan*/  spinlock; } ;
struct sst_byt {struct sst_generic_ipc ipc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int IPC_HEADER_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPC_HEADER_DATA_MASK ; 
 int IPC_NOTIFICATION ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int SST_BYT_IMRX_REQUEST ; 
 int SST_BYT_IPCD_BUSY ; 
 int SST_BYT_IPCD_DONE ; 
 int /*<<< orphan*/  SST_IMRX ; 
 int /*<<< orphan*/  SST_IPCD ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sst_byt_process_notification (struct sst_byt*,unsigned long*) ; 
 int /*<<< orphan*/  sst_byt_process_reply (struct sst_byt*,int) ; 
 struct sst_byt* sst_dsp_get_thread_context (struct sst_dsp*) ; 
 int sst_dsp_shim_read64_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits64_unlocked (struct sst_dsp*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t sst_byt_irq_thread(int irq, void *context)
{
	struct sst_dsp *sst = (struct sst_dsp *) context;
	struct sst_byt *byt = sst_dsp_get_thread_context(sst);
	struct sst_generic_ipc *ipc = &byt->ipc;
	u64 header;
	unsigned long flags;

	spin_lock_irqsave(&sst->spinlock, flags);

	header = sst_dsp_shim_read64_unlocked(sst, SST_IPCD);
	if (header & SST_BYT_IPCD_BUSY) {
		if (header & IPC_NOTIFICATION) {
			/* message from ADSP */
			sst_byt_process_notification(byt, &flags);
		} else {
			/* reply from ADSP */
			sst_byt_process_reply(byt, header);
		}
		/*
		 * clear IPCD BUSY bit and set DONE bit. Tell DSP we have
		 * processed the message and can accept new. Clear data part
		 * of the header
		 */
		sst_dsp_shim_update_bits64_unlocked(sst, SST_IPCD,
			SST_BYT_IPCD_DONE | SST_BYT_IPCD_BUSY |
			IPC_HEADER_DATA(IPC_HEADER_DATA_MASK),
			SST_BYT_IPCD_DONE);
		/* unmask message request interrupts */
		sst_dsp_shim_update_bits64_unlocked(sst, SST_IMRX,
			SST_BYT_IMRX_REQUEST, 0);
	}

	spin_unlock_irqrestore(&sst->spinlock, flags);

	/* continue to send any remaining messages... */
	schedule_work(&ipc->kwork);

	return IRQ_HANDLED;
}