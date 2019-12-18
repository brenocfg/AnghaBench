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
struct snd_sof_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HDA_DSP_CTRL_RESET_TIMEOUT ; 
 int /*<<< orphan*/  HDA_DSP_HDA_BAR ; 
 int /*<<< orphan*/  SOF_HDA_GCTL ; 
 int SOF_HDA_GCTL_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int snd_sof_dsp_read (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int hda_dsp_ctrl_link_reset(struct snd_sof_dev *sdev, bool reset)
{
	unsigned long timeout;
	u32 gctl = 0;
	u32 val;

	/* 0 to enter reset and 1 to exit reset */
	val = reset ? 0 : SOF_HDA_GCTL_RESET;

	/* enter/exit HDA controller reset */
	snd_sof_dsp_update_bits(sdev, HDA_DSP_HDA_BAR, SOF_HDA_GCTL,
				SOF_HDA_GCTL_RESET, val);

	/* wait to enter/exit reset */
	timeout = jiffies + msecs_to_jiffies(HDA_DSP_CTRL_RESET_TIMEOUT);
	while (time_before(jiffies, timeout)) {
		gctl = snd_sof_dsp_read(sdev, HDA_DSP_HDA_BAR, SOF_HDA_GCTL);
		if ((gctl & SOF_HDA_GCTL_RESET) == val)
			return 0;
		usleep_range(500, 1000);
	}

	/* enter/exit reset failed */
	dev_err(sdev->dev, "error: failed to %s HDA controller gctl 0x%x\n",
		reset ? "reset" : "ready", gctl);
	return -EIO;
}