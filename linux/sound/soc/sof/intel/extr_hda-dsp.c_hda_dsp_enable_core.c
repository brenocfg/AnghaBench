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
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 scalar_t__ hda_dsp_core_is_enabled (struct snd_sof_dev*,unsigned int) ; 
 int hda_dsp_core_power_up (struct snd_sof_dev*,unsigned int) ; 
 int hda_dsp_core_run (struct snd_sof_dev*,unsigned int) ; 

int hda_dsp_enable_core(struct snd_sof_dev *sdev, unsigned int core_mask)
{
	int ret;

	/* return if core is already enabled */
	if (hda_dsp_core_is_enabled(sdev, core_mask))
		return 0;

	/* power up */
	ret = hda_dsp_core_power_up(sdev, core_mask);
	if (ret < 0) {
		dev_err(sdev->dev, "error: dsp core power up failed: core_mask %x\n",
			core_mask);
		return ret;
	}

	return hda_dsp_core_run(sdev, core_mask);
}