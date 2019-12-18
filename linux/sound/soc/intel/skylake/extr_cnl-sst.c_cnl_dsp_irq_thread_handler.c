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
 int CNL_ADSPIS_IPC ; 
 int /*<<< orphan*/  CNL_ADSP_REG_HIPCCTL ; 
 int /*<<< orphan*/  CNL_ADSP_REG_HIPCCTL_DONE ; 
 int /*<<< orphan*/  CNL_ADSP_REG_HIPCIDA ; 
 int CNL_ADSP_REG_HIPCIDA_DONE ; 
 int /*<<< orphan*/  CNL_ADSP_REG_HIPCTDA ; 
 int CNL_ADSP_REG_HIPCTDA_DONE ; 
 int /*<<< orphan*/  CNL_ADSP_REG_HIPCTDD ; 
 int /*<<< orphan*/  CNL_ADSP_REG_HIPCTDR ; 
 int CNL_ADSP_REG_HIPCTDR_BUSY ; 
 scalar_t__ CNL_IPC_GLB_NOTIFY_RSP_TYPE (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  cnl_ipc_int_enable (struct sst_dsp*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skl_ipc_process_notification (struct sst_generic_ipc*,struct skl_ipc_header) ; 
 int /*<<< orphan*/  skl_ipc_process_reply (struct sst_generic_ipc*,struct skl_ipc_header) ; 
 struct skl_dev* sst_dsp_get_thread_context (struct sst_dsp*) ; 
 int sst_dsp_shim_read_unlocked (struct sst_dsp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits (struct sst_dsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sst_dsp_shim_update_bits_forced (struct sst_dsp*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t cnl_dsp_irq_thread_handler(int irq, void *context)
{
	struct sst_dsp *dsp = context;
	struct skl_dev *cnl = sst_dsp_get_thread_context(dsp);
	struct sst_generic_ipc *ipc = &cnl->ipc;
	struct skl_ipc_header header = {0};
	u32 hipcida, hipctdr, hipctdd;
	int ipc_irq = 0;

	/* here we handle ipc interrupts only */
	if (!(dsp->intr_status & CNL_ADSPIS_IPC))
		return IRQ_NONE;

	hipcida = sst_dsp_shim_read_unlocked(dsp, CNL_ADSP_REG_HIPCIDA);
	hipctdr = sst_dsp_shim_read_unlocked(dsp, CNL_ADSP_REG_HIPCTDR);
	hipctdd = sst_dsp_shim_read_unlocked(dsp, CNL_ADSP_REG_HIPCTDD);

	/* reply message from dsp */
	if (hipcida & CNL_ADSP_REG_HIPCIDA_DONE) {
		sst_dsp_shim_update_bits(dsp, CNL_ADSP_REG_HIPCCTL,
			CNL_ADSP_REG_HIPCCTL_DONE, 0);

		/* clear done bit - tell dsp operation is complete */
		sst_dsp_shim_update_bits_forced(dsp, CNL_ADSP_REG_HIPCIDA,
			CNL_ADSP_REG_HIPCIDA_DONE, CNL_ADSP_REG_HIPCIDA_DONE);

		ipc_irq = 1;

		/* unmask done interrupt */
		sst_dsp_shim_update_bits(dsp, CNL_ADSP_REG_HIPCCTL,
			CNL_ADSP_REG_HIPCCTL_DONE, CNL_ADSP_REG_HIPCCTL_DONE);
	}

	/* new message from dsp */
	if (hipctdr & CNL_ADSP_REG_HIPCTDR_BUSY) {
		header.primary = hipctdr;
		header.extension = hipctdd;
		dev_dbg(dsp->dev, "IPC irq: Firmware respond primary:%x",
						header.primary);
		dev_dbg(dsp->dev, "IPC irq: Firmware respond extension:%x",
						header.extension);

		if (CNL_IPC_GLB_NOTIFY_RSP_TYPE(header.primary)) {
			/* Handle Immediate reply from DSP Core */
			skl_ipc_process_reply(ipc, header);
		} else {
			dev_dbg(dsp->dev, "IPC irq: Notification from firmware\n");
			skl_ipc_process_notification(ipc, header);
		}
		/* clear busy interrupt */
		sst_dsp_shim_update_bits_forced(dsp, CNL_ADSP_REG_HIPCTDR,
			CNL_ADSP_REG_HIPCTDR_BUSY, CNL_ADSP_REG_HIPCTDR_BUSY);

		/* set done bit to ack dsp */
		sst_dsp_shim_update_bits_forced(dsp, CNL_ADSP_REG_HIPCTDA,
			CNL_ADSP_REG_HIPCTDA_DONE, CNL_ADSP_REG_HIPCTDA_DONE);
		ipc_irq = 1;
	}

	if (ipc_irq == 0)
		return IRQ_NONE;

	cnl_ipc_int_enable(dsp);

	/* continue to send any remaining messages */
	schedule_work(&ipc->kwork);

	return IRQ_HANDLED;
}