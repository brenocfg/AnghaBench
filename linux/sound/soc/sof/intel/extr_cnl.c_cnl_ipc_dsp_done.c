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
 int /*<<< orphan*/  CNL_DSP_REG_HIPCCTL ; 
 int /*<<< orphan*/  CNL_DSP_REG_HIPCCTL_DONE ; 
 int /*<<< orphan*/  CNL_DSP_REG_HIPCIDA ; 
 int /*<<< orphan*/  CNL_DSP_REG_HIPCIDA_DONE ; 
 int /*<<< orphan*/  HDA_DSP_BAR ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits_forced (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnl_ipc_dsp_done(struct snd_sof_dev *sdev)
{
	/*
	 * set DONE bit - tell DSP we have received the reply msg
	 * from DSP, and processed it, don't send more reply to host
	 */
	snd_sof_dsp_update_bits_forced(sdev, HDA_DSP_BAR,
				       CNL_DSP_REG_HIPCIDA,
				       CNL_DSP_REG_HIPCIDA_DONE,
				       CNL_DSP_REG_HIPCIDA_DONE);

	/* unmask Done interrupt */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR,
				CNL_DSP_REG_HIPCCTL,
				CNL_DSP_REG_HIPCCTL_DONE,
				CNL_DSP_REG_HIPCCTL_DONE);
}