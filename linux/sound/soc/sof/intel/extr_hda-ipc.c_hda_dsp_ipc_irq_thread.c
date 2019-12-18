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
 int /*<<< orphan*/  HDA_DSP_ADSPIC_IPC ; 
 int /*<<< orphan*/  HDA_DSP_BAR ; 
 int /*<<< orphan*/  HDA_DSP_PANIC_OFFSET (int) ; 
 int /*<<< orphan*/  HDA_DSP_REG_ADSPIC ; 
 int /*<<< orphan*/  HDA_DSP_REG_HIPCCTL ; 
 int /*<<< orphan*/  HDA_DSP_REG_HIPCCTL_BUSY ; 
 int /*<<< orphan*/  HDA_DSP_REG_HIPCCTL_DONE ; 
 int /*<<< orphan*/  HDA_DSP_REG_HIPCI ; 
 int /*<<< orphan*/  HDA_DSP_REG_HIPCIE ; 
 int HDA_DSP_REG_HIPCIE_DONE ; 
 int HDA_DSP_REG_HIPCIE_MSG_MASK ; 
 int HDA_DSP_REG_HIPCI_MSG_MASK ; 
 int /*<<< orphan*/  HDA_DSP_REG_HIPCT ; 
 int /*<<< orphan*/  HDA_DSP_REG_HIPCTE ; 
 int HDA_DSP_REG_HIPCTE_MSG_MASK ; 
 int HDA_DSP_REG_HIPCT_BUSY ; 
 int HDA_DSP_REG_HIPCT_MSG_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int SOF_IPC_PANIC_MAGIC ; 
 int SOF_IPC_PANIC_MAGIC_MASK ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  hda_dsp_ipc_dsp_done (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  hda_dsp_ipc_get_reply (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  hda_dsp_ipc_host_done (struct snd_sof_dev*) ; 
 scalar_t__ hda_dsp_ipc_is_sof (int) ; 
 int /*<<< orphan*/  snd_sof_dsp_panic (struct snd_sof_dev*,int /*<<< orphan*/ ) ; 
 int snd_sof_dsp_read (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_ipc_msgs_rx (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  snd_sof_ipc_reply (struct snd_sof_dev*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

irqreturn_t hda_dsp_ipc_irq_thread(int irq, void *context)
{
	struct snd_sof_dev *sdev = context;
	u32 hipci;
	u32 hipcie;
	u32 hipct;
	u32 hipcte;
	u32 msg;
	u32 msg_ext;
	bool ipc_irq = false;

	/* read IPC status */
	hipcie = snd_sof_dsp_read(sdev, HDA_DSP_BAR,
				  HDA_DSP_REG_HIPCIE);
	hipct = snd_sof_dsp_read(sdev, HDA_DSP_BAR, HDA_DSP_REG_HIPCT);
	hipci = snd_sof_dsp_read(sdev, HDA_DSP_BAR, HDA_DSP_REG_HIPCI);
	hipcte = snd_sof_dsp_read(sdev, HDA_DSP_BAR, HDA_DSP_REG_HIPCTE);

	/* is this a reply message from the DSP */
	if (hipcie & HDA_DSP_REG_HIPCIE_DONE) {
		msg = hipci & HDA_DSP_REG_HIPCI_MSG_MASK;
		msg_ext = hipcie & HDA_DSP_REG_HIPCIE_MSG_MASK;

		dev_vdbg(sdev->dev,
			 "ipc: firmware response, msg:0x%x, msg_ext:0x%x\n",
			 msg, msg_ext);

		/* mask Done interrupt */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR,
					HDA_DSP_REG_HIPCCTL,
					HDA_DSP_REG_HIPCCTL_DONE, 0);

		/*
		 * Make sure the interrupt thread cannot be preempted between
		 * waking up the sender and re-enabling the interrupt. Also
		 * protect against a theoretical race with sof_ipc_tx_message():
		 * if the DSP is fast enough to receive an IPC message, reply to
		 * it, and the host interrupt processing calls this function on
		 * a different core from the one, where the sending is taking
		 * place, the message might not yet be marked as expecting a
		 * reply.
		 */
		spin_lock_irq(&sdev->ipc_lock);

		/* handle immediate reply from DSP core - ignore ROM messages */
		if (hda_dsp_ipc_is_sof(msg)) {
			hda_dsp_ipc_get_reply(sdev);
			snd_sof_ipc_reply(sdev, msg);
		}

		/* wake up sleeper if we are loading code */
		if (sdev->code_loading)	{
			sdev->code_loading = 0;
			wake_up(&sdev->waitq);
		}

		/* set the done bit */
		hda_dsp_ipc_dsp_done(sdev);

		spin_unlock_irq(&sdev->ipc_lock);

		ipc_irq = true;
	}

	/* is this a new message from DSP */
	if (hipct & HDA_DSP_REG_HIPCT_BUSY) {
		msg = hipct & HDA_DSP_REG_HIPCT_MSG_MASK;
		msg_ext = hipcte & HDA_DSP_REG_HIPCTE_MSG_MASK;

		dev_vdbg(sdev->dev,
			 "ipc: firmware initiated, msg:0x%x, msg_ext:0x%x\n",
			 msg, msg_ext);

		/* mask BUSY interrupt */
		snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR,
					HDA_DSP_REG_HIPCCTL,
					HDA_DSP_REG_HIPCCTL_BUSY, 0);

		/* handle messages from DSP */
		if ((hipct & SOF_IPC_PANIC_MAGIC_MASK) == SOF_IPC_PANIC_MAGIC) {
			/* this is a PANIC message !! */
			snd_sof_dsp_panic(sdev, HDA_DSP_PANIC_OFFSET(msg_ext));
		} else {
			/* normal message - process normally */
			snd_sof_ipc_msgs_rx(sdev);
		}

		hda_dsp_ipc_host_done(sdev);

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