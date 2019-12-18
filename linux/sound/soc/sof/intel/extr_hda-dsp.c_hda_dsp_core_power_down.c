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
struct snd_sof_dev {int dummy; } ;

/* Variables and functions */
 int HDA_DSP_ADSPCS_SPA_MASK (unsigned int) ; 
 int /*<<< orphan*/  HDA_DSP_BAR ; 
 int HDA_DSP_PD_TIMEOUT ; 
 int /*<<< orphan*/  HDA_DSP_REG_ADSPCS ; 
 int /*<<< orphan*/  HDA_DSP_REG_POLL_INTERVAL_US ; 
 int USEC_PER_MSEC ; 
 int snd_sof_dsp_read_poll_timeout (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits_unlocked (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int hda_dsp_core_power_down(struct snd_sof_dev *sdev, unsigned int core_mask)
{
	u32 adspcs;

	/* update bits */
	snd_sof_dsp_update_bits_unlocked(sdev, HDA_DSP_BAR,
					 HDA_DSP_REG_ADSPCS,
					 HDA_DSP_ADSPCS_SPA_MASK(core_mask), 0);

	return snd_sof_dsp_read_poll_timeout(sdev, HDA_DSP_BAR,
				HDA_DSP_REG_ADSPCS, adspcs,
				!(adspcs & HDA_DSP_ADSPCS_SPA_MASK(core_mask)),
				HDA_DSP_REG_POLL_INTERVAL_US,
				HDA_DSP_PD_TIMEOUT * USEC_PER_MSEC);
}