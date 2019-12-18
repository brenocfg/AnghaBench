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
struct snd_sof_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_DSP_BAR ; 
 int /*<<< orphan*/  HDA_DSP_REG_HIPCCTL ; 
 int /*<<< orphan*/  HDA_DSP_REG_HIPCCTL_BUSY ; 
 int /*<<< orphan*/  HDA_DSP_REG_HIPCT ; 
 int /*<<< orphan*/  HDA_DSP_REG_HIPCT_BUSY ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits_forced (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hda_dsp_ipc_host_done(struct snd_sof_dev *sdev)
{
	/*
	 * tell DSP cmd is done - clear busy
	 * interrupt and send reply msg to dsp
	 */
	snd_sof_dsp_update_bits_forced(sdev, HDA_DSP_BAR,
				       HDA_DSP_REG_HIPCT,
				       HDA_DSP_REG_HIPCT_BUSY,
				       HDA_DSP_REG_HIPCT_BUSY);

	/* unmask BUSY interrupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR,
				HDA_DSP_REG_HIPCCTL,
				HDA_DSP_REG_HIPCCTL_BUSY,
				HDA_DSP_REG_HIPCCTL_BUSY);
}