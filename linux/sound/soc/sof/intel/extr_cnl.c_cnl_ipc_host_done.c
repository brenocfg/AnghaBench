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
 int /*<<< orphan*/  CNL_DSP_REG_HIPCTDA ; 
 int /*<<< orphan*/  CNL_DSP_REG_HIPCTDA_DONE ; 
 int /*<<< orphan*/  CNL_DSP_REG_HIPCTDR ; 
 int /*<<< orphan*/  CNL_DSP_REG_HIPCTDR_BUSY ; 
 int /*<<< orphan*/  HDA_DSP_BAR ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits_forced (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnl_ipc_host_done(struct snd_sof_dev *sdev)
{
	/*
	 * clear busy interrupt to tell dsp controller this
	 * interrupt has been accepted, not trigger it again
	 */
	snd_sof_dsp_update_bits_forced(sdev, HDA_DSP_BAR,
				       CNL_DSP_REG_HIPCTDR,
				       CNL_DSP_REG_HIPCTDR_BUSY,
				       CNL_DSP_REG_HIPCTDR_BUSY);
	/*
	 * set done bit to ack dsp the msg has been
	 * processed and send reply msg to dsp
	 */
	snd_sof_dsp_update_bits_forced(sdev, HDA_DSP_BAR,
				       CNL_DSP_REG_HIPCTDA,
				       CNL_DSP_REG_HIPCTDA_DONE,
				       CNL_DSP_REG_HIPCTDA_DONE);
}