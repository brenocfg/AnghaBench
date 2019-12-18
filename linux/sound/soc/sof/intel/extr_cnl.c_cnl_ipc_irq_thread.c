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
struct snd_sof_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  ipc_lock; int /*<<< orphan*/  waitq; scalar_t__ code_loading; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_DSP_REG_HIPCCTL ; 
 int /*<<< orphan*/  CNL_DSP_REG_HIPCCTL_DONE ; 
 int /*<<< orphan*/  CNL_DSP_REG_HIPCIDA ; 
 int CNL_DSP_REG_HIPCIDA_DONE ; 
 int CNL_DSP_REG_HIPCIDA_MSG_MASK ; 
 int /*<<< orphan*/  CNL_DSP_REG_HIPCIDR ; 
 int CNL_DSP_REG_HIPCIDR_MSG_MASK ; 
 int /*<<< orphan*/  CNL_DSP_REG_HIPCTDD ; 
 int CNL_DSP_REG_HIPCTDD_MSG_MASK ; 
 int /*<<< orphan*/  CNL_DSP_REG_HIPCTDR ; 
 int CNL_DSP_REG_HIPCTDR_BUSY ; 
 int CNL_DSP_REG_HIPCTDR_MSG_MASK ; 
 int /*<<< orphan*/  HDA_DSP_ADSPIC_IPC ; 
 int /*<<< orphan*/  HDA_DSP_BAR ; 
 int /*<<< orphan*/  HDA_DSP_PANIC_OFFSET (int) ; 
 int /*<<< orphan*/  HDA_DSP_REG_ADSPIC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int SOF_IPC_PANIC_MAGIC ; 
 int SOF_IPC_PANIC_MAGIC_MASK ; 
 int /*<<< orphan*/  cnl_ipc_dsp_done (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  cnl_ipc_host_done (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  hda_dsp_ipc_get_reply (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  snd_sof_dsp_panic (struct snd_sof_dev*,int /*<<< orphan*/ ) ; 
 int snd_sof_dsp_read (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_ipc_msgs_rx (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  snd_sof_ipc_reply (struct snd_sof_dev*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cnl_ipc_irq_thread(int irq, void *context)
{
	struct snd_sof_dev *sdev = context;
	u32 hipci;
	u32 hipcida;
	u32 hipctdr;
	u32 hipctdd;
	u32 msg;
	u32 msg_ext;
	bool ipc_irq = false;

	hipcida = snd_sof_dsp_read(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCIDA);
	hipctdr = snd_sof_dsp_read(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCTDR);
	hipctdd = snd_sof_dsp_read(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCTDD);
	hipci = snd_sof_dsp_read(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCIDR);

	/* reply message from DSP */
	if (hipcida & CNL_DSP_REG_HIPCIDA_DONE) {
		msg_ext = hipci & CNL_DSP_REG_HIPCIDR_MSG_MASK;
		msg = hipcida & CNL_DSP_REG_HIPCIDA_MSG_MASK;

		dev_vdbg(sdev->dev,
			 "ipc: firmware response, msg:0x%x, msg_ext:0x%x\n",
			 msg, msg_ext);

		/* mask Done interrupt */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR,
					CNL_DSP_REG_HIPCCTL,
					CNL_DSP_REG_HIPCCTL_DONE, 0);

		spin_lock_irq(&sdev->ipc_lock);

		/* handle immediate reply from DSP core */
		hda_dsp_ipc_get_reply(sdev);
		snd_sof_ipc_reply(sdev, msg);

		if (sdev->code_loading)	{
			sdev->code_loading = 0;
			wake_up(&sdev->waitq);
		}

		cnl_ipc_dsp_done(sdev);

		spin_unlock_irq(&sdev->ipc_lock);

		ipc_irq = true;
	}

	/* new message from DSP */
	if (hipctdr & CNL_DSP_REG_HIPCTDR_BUSY) {
		msg = hipctdr & CNL_DSP_REG_HIPCTDR_MSG_MASK;
		msg_ext = hipctdd & CNL_DSP_REG_HIPCTDD_MSG_MASK;

		dev_vdbg(sdev->dev,
			 "ipc: firmware initiated, msg:0x%x, msg_ext:0x%x\n",
			 msg, msg_ext);

		/* handle messages from DSP */
		if ((hipctdr & SOF_IPC_PANIC_MAGIC_MASK) ==
		   SOF_IPC_PANIC_MAGIC) {
			snd_sof_dsp_panic(sdev, HDA_DSP_PANIC_OFFSET(msg_ext));
		} else {
			snd_sof_ipc_msgs_rx(sdev);
		}

		cnl_ipc_host_done(sdev);

		ipc_irq = true;
	}

	if (!ipc_irq) {
		/*
		 * This interrupt is not shared so no need to return IRQ_NONE.
		 */
		dev_dbg_ratelimited(sdev->dev,
				    "nothing to do in IPC IRQ thread\n");
	}

	/* re-enable IPC interrupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR, HDA_DSP_REG_ADSPIC,
				HDA_DSP_ADSPIC_IPC, HDA_DSP_ADSPIC_IPC);

	return IRQ_HANDLED;
}