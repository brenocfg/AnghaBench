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
typedef  unsigned int u32 ;
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int HDA_DSP_ADSPCS_CPA_MASK (unsigned int) ; 
 int /*<<< orphan*/  HDA_DSP_ADSPCS_SPA_MASK (unsigned int) ; 
 int /*<<< orphan*/  HDA_DSP_BAR ; 
 int /*<<< orphan*/  HDA_DSP_REG_ADSPCS ; 
 int /*<<< orphan*/  HDA_DSP_REG_POLL_INTERVAL_US ; 
 int /*<<< orphan*/  HDA_DSP_RESET_TIMEOUT_US ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int snd_sof_dsp_read (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_sof_dsp_read_poll_timeout (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hda_dsp_core_power_up(struct snd_sof_dev *sdev, unsigned int core_mask)
{
	unsigned int cpa;
	u32 adspcs;
	int ret;

	/* update bits */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_BAR, HDA_DSP_REG_ADSPCS,
				HDA_DSP_ADSPCS_SPA_MASK(core_mask),
				HDA_DSP_ADSPCS_SPA_MASK(core_mask));

	/* poll with timeout to check if operation successful */
	cpa = HDA_DSP_ADSPCS_CPA_MASK(core_mask);
	ret = snd_sof_dsp_read_poll_timeout(sdev, HDA_DSP_BAR,
					    HDA_DSP_REG_ADSPCS, adspcs,
					    (adspcs & cpa) == cpa,
					    HDA_DSP_REG_POLL_INTERVAL_US,
					    HDA_DSP_RESET_TIMEOUT_US);
	if (ret < 0)
		dev_err(sdev->dev, "error: timeout on core powerup\n");

	/* did core power up ? */
	adspcs = snd_sof_dsp_read(sdev, HDA_DSP_BAR,
				  HDA_DSP_REG_ADSPCS);
	if ((adspcs & HDA_DSP_ADSPCS_CPA_MASK(core_mask)) !=
		HDA_DSP_ADSPCS_CPA_MASK(core_mask)) {
		dev_err(sdev->dev,
			"error: power up core failed core_mask %xadspcs 0x%x\n",
			core_mask, adspcs);
		ret = -EIO;
	}

	return ret;
}