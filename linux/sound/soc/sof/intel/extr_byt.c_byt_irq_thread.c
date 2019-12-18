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
struct snd_sof_dev {int /*<<< orphan*/  ipc_lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BYT_DSP_BAR ; 
 scalar_t__ BYT_PANIC_OFFSET (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ MBOX_OFFSET ; 
 int SHIM_BYT_IPCD_BUSY ; 
 int SHIM_BYT_IPCX_DONE ; 
 int /*<<< orphan*/  SHIM_IMRX ; 
 int SHIM_IMRX_BUSY ; 
 int SHIM_IMRX_DONE ; 
 int /*<<< orphan*/  SHIM_IPCD ; 
 int /*<<< orphan*/  SHIM_IPCX ; 
 int SOF_IPC_PANIC_MAGIC ; 
 int SOF_IPC_PANIC_MAGIC_MASK ; 
 int /*<<< orphan*/  byt_dsp_done (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  byt_get_reply (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  byt_host_done (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  snd_sof_dsp_panic (struct snd_sof_dev*,scalar_t__) ; 
 int snd_sof_dsp_read64 (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits64_unlocked (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_sof_ipc_msgs_rx (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  snd_sof_ipc_reply (struct snd_sof_dev*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t byt_irq_thread(int irq, void *context)
{
	struct snd_sof_dev *sdev = context;
	u64 ipcx, ipcd;
	u64 imrx;

	imrx = snd_sof_dsp_read64(sdev, BYT_DSP_BAR, SHIM_IMRX);
	ipcx = snd_sof_dsp_read64(sdev, BYT_DSP_BAR, SHIM_IPCX);

	/* reply message from DSP */
	if (ipcx & SHIM_BYT_IPCX_DONE &&
	    !(imrx & SHIM_IMRX_DONE)) {
		/* Mask Done interrupt before first */
		snd_sof_dsp_update_bits64_unlocked(sdev, BYT_DSP_BAR,
						   SHIM_IMRX,
						   SHIM_IMRX_DONE,
						   SHIM_IMRX_DONE);

		spin_lock_irq(&sdev->ipc_lock);

		/*
		 * handle immediate reply from DSP core. If the msg is
		 * found, set done bit in cmd_done which is called at the
		 * end of message processing function, else set it here
		 * because the done bit can't be set in cmd_done function
		 * which is triggered by msg
		 */
		byt_get_reply(sdev);
		snd_sof_ipc_reply(sdev, ipcx);

		byt_dsp_done(sdev);

		spin_unlock_irq(&sdev->ipc_lock);
	}

	/* new message from DSP */
	ipcd = snd_sof_dsp_read64(sdev, BYT_DSP_BAR, SHIM_IPCD);
	if (ipcd & SHIM_BYT_IPCD_BUSY &&
	    !(imrx & SHIM_IMRX_BUSY)) {
		/* Mask Busy interrupt before return */
		snd_sof_dsp_update_bits64_unlocked(sdev, BYT_DSP_BAR,
						   SHIM_IMRX,
						   SHIM_IMRX_BUSY,
						   SHIM_IMRX_BUSY);

		/* Handle messages from DSP Core */
		if ((ipcd & SOF_IPC_PANIC_MAGIC_MASK) == SOF_IPC_PANIC_MAGIC) {
			snd_sof_dsp_panic(sdev, BYT_PANIC_OFFSET(ipcd) +
					  MBOX_OFFSET);
		} else {
			snd_sof_ipc_msgs_rx(sdev);
		}

		byt_host_done(sdev);
	}

	return IRQ_HANDLED;
}