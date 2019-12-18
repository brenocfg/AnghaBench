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
struct snd_sof_dev {int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  dev; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_DSP_ADSPIC_IPC ; 
 int HDA_DSP_ADSPIS_IPC ; 
 int /*<<< orphan*/  HDA_DSP_BAR ; 
 int /*<<< orphan*/  HDA_DSP_REG_ADSPIC ; 
 int /*<<< orphan*/  HDA_DSP_REG_ADSPIS ; 
 int IRQ_NONE ; 
 int IRQ_WAKE_THREAD ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int) ; 
 int snd_sof_dsp_read (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits_unlocked (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

irqreturn_t hda_dsp_ipc_irq_handler(int irq, void *context)
{
	struct snd_sof_dev *sdev = context;
	int ret = IRQ_NONE;
	u32 irq_status;

	spin_lock(&sdev->hw_lock);

	/* store status */
	irq_status = snd_sof_dsp_read(sdev, HDA_DSP_BAR, HDA_DSP_REG_ADSPIS);
	dev_vdbg(sdev->dev, "irq handler: irq_status:0x%x\n", irq_status);

	/* invalid message ? */
	if (irq_status == 0xffffffff)
		goto out;

	/* IPC message ? */
	if (irq_status & HDA_DSP_ADSPIS_IPC) {
		/* disable IPC interrupt */
		snd_sof_dsp_update_bits_unlocked(sdev, HDA_DSP_BAR,
						 HDA_DSP_REG_ADSPIC,
						 HDA_DSP_ADSPIC_IPC, 0);
		ret = IRQ_WAKE_THREAD;
	}

out:
	spin_unlock(&sdev->hw_lock);
	return ret;
}