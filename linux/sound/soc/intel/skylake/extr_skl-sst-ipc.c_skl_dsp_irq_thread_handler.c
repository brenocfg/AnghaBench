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
struct sst_dsp {int intr_status; int /*<<< orphan*/  dev; } ;
struct skl_ipc_header {int primary; int extension; int /*<<< orphan*/  member_0; } ;
struct skl_dev {struct sst_generic_ipc ipc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ IPC_GLB_NOTIFY_RSP_TYPE (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int SKL_ADSPIS_CL_DMA ; 
 int SKL_ADSPIS_IPC ; 
 int /*<<< orphan*/  SKL_ADSP_REG_HIPCCTL ; 
 int /*<<< orphan*/  SKL_ADSP_REG_HIPCCTL_DONE ; 
 int /*<<< orphan*/  SKL_ADSP_REG_HIPCIE ; 
 int SKL_ADSP_REG_HIPCIE_DONE ; 
 int /*<<< orphan*/  SKL_ADSP_REG_HIPCT ; 
 int /*<<< orphan*/  SKL_ADSP_REG_HIPCTE ; 
 int SKL_ADSP_REG_HIPCT_BUSY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skl_cldma_process_intr (struct sst_dsp*) ; 
 int /*<<< orphan*/  skl_ipc_int_enable (struct sst_dsp*) ; 
 int /*<<< orphan*/  skl_ipc_process_notification (struct sst_generic_ipc*,struct skl_ipc_header) ; 
 int /*<<< orphan*/  skl_ipc_process_reply (struct sst_generic_ipc*,struct skl_ipc_header) ; 
 struct skl_dev* sst_dsp_get_thread_context (struct sst_dsp*) ; 
 int sst_dsp_shim_read_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits_forced (struct sst_dsp*,int /*<<< orphan*/ ,int,int) ; 

irqreturn_t skl_dsp_irq_thread_handler(int irq, void *context)
{
	struct sst_dsp *dsp = context;
	struct skl_dev *skl = sst_dsp_get_thread_context(dsp);
	struct sst_generic_ipc *ipc = &skl->ipc;
	struct skl_ipc_header header = {0};
	u32 hipcie, hipct, hipcte;
	int ipc_irq = 0;

	if (dsp->intr_status & SKL_ADSPIS_CL_DMA)
		skl_cldma_process_intr(dsp);

	/* Here we handle IPC interrupts only */
	if (!(dsp->intr_status & SKL_ADSPIS_IPC))
		return IRQ_NONE;

	hipcie = sst_dsp_shim_read_unlocked(dsp, SKL_ADSP_REG_HIPCIE);
	hipct = sst_dsp_shim_read_unlocked(dsp, SKL_ADSP_REG_HIPCT);
	hipcte = sst_dsp_shim_read_unlocked(dsp, SKL_ADSP_REG_HIPCTE);

	/* reply message from DSP */
	if (hipcie & SKL_ADSP_REG_HIPCIE_DONE) {
		sst_dsp_shim_update_bits(dsp, SKL_ADSP_REG_HIPCCTL,
			SKL_ADSP_REG_HIPCCTL_DONE, 0);

		/* clear DONE bit - tell DSP we have completed the operation */
		sst_dsp_shim_update_bits_forced(dsp, SKL_ADSP_REG_HIPCIE,
			SKL_ADSP_REG_HIPCIE_DONE, SKL_ADSP_REG_HIPCIE_DONE);

		ipc_irq = 1;

		/* unmask Done interrupt */
		sst_dsp_shim_update_bits(dsp, SKL_ADSP_REG_HIPCCTL,
			SKL_ADSP_REG_HIPCCTL_DONE, SKL_ADSP_REG_HIPCCTL_DONE);
	}

	/* New message from DSP */
	if (hipct & SKL_ADSP_REG_HIPCT_BUSY) {
		header.primary = hipct;
		header.extension = hipcte;
		dev_dbg(dsp->dev, "IPC irq: Firmware respond primary:%x\n",
						header.primary);
		dev_dbg(dsp->dev, "IPC irq: Firmware respond extension:%x\n",
						header.extension);

		if (IPC_GLB_NOTIFY_RSP_TYPE(header.primary)) {
			/* Handle Immediate reply from DSP Core */
			skl_ipc_process_reply(ipc, header);
		} else {
			dev_dbg(dsp->dev, "IPC irq: Notification from firmware\n");
			skl_ipc_process_notification(ipc, header);
		}
		/* clear  busy interrupt */
		sst_dsp_shim_update_bits_forced(dsp, SKL_ADSP_REG_HIPCT,
			SKL_ADSP_REG_HIPCT_BUSY, SKL_ADSP_REG_HIPCT_BUSY);
		ipc_irq = 1;
	}

	if (ipc_irq == 0)
		return IRQ_NONE;

	skl_ipc_int_enable(dsp);

	/* continue to send any remaining messages... */
	schedule_work(&ipc->kwork);

	return IRQ_HANDLED;
}