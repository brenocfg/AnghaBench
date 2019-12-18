#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sof_intel_hda_dev {struct sof_intel_dsp_desc* desc; } ;
struct sof_intel_dsp_desc {int /*<<< orphan*/  ipc_ctl; } ;
struct snd_sof_dev {TYPE_1__* pdata; } ;
struct TYPE_2__ {struct sof_intel_hda_dev* hw_pdata; } ;

/* Variables and functions */
 int HDA_DSP_ADSPIC_IPC ; 
 int /*<<< orphan*/  HDA_DSP_BAR ; 
 int /*<<< orphan*/  HDA_DSP_REG_ADSPIC ; 
 int HDA_DSP_REG_HIPCCTL_BUSY ; 
 int HDA_DSP_REG_HIPCCTL_DONE ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void hda_dsp_ipc_int_enable(struct snd_sof_dev *sdev)
{
	struct sof_intel_hda_dev *hda = sdev->pdata->hw_pdata;
	const struct sof_intel_dsp_desc *chip = hda->desc;

	/* enable IPC DONE and BUSY interrupts */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR, chip->ipc_ctl,
			HDA_DSP_REG_HIPCCTL_DONE | HDA_DSP_REG_HIPCCTL_BUSY,
			HDA_DSP_REG_HIPCCTL_DONE | HDA_DSP_REG_HIPCCTL_BUSY);

	/* enable IPC interrupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR, HDA_DSP_REG_ADSPIC,
				HDA_DSP_ADSPIC_IPC, HDA_DSP_ADSPIC_IPC);
}