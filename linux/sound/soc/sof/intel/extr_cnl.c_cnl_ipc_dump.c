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
typedef  int /*<<< orphan*/  u32 ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNL_DSP_REG_HIPCCTL ; 
 int /*<<< orphan*/  CNL_DSP_REG_HIPCIDA ; 
 int /*<<< orphan*/  CNL_DSP_REG_HIPCTDR ; 
 int /*<<< orphan*/  HDA_DSP_BAR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hda_ipc_irq_dump (struct snd_sof_dev*) ; 
 int /*<<< orphan*/  snd_sof_dsp_read (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnl_ipc_dump(struct snd_sof_dev *sdev)
{
	u32 hipcctl;
	u32 hipcida;
	u32 hipctdr;

	hda_ipc_irq_dump(sdev);

	/* read IPC status */
	hipcida = snd_sof_dsp_read(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCIDA);
	hipcctl = snd_sof_dsp_read(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCCTL);
	hipctdr = snd_sof_dsp_read(sdev, HDA_DSP_BAR, CNL_DSP_REG_HIPCTDR);

	/* dump the IPC regs */
	/* TODO: parse the raw msg */
	dev_err(sdev->dev,
		"error: host status 0x%8.8x dsp status 0x%8.8x mask 0x%8.8x\n",
		hipcida, hipctdr, hipcctl);
}