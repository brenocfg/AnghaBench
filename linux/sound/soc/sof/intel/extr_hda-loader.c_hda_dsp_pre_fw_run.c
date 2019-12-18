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
 int hda_dsp_ctrl_clock_power_gating (struct snd_sof_dev*,int) ; 

int hda_dsp_pre_fw_run(struct snd_sof_dev *sdev)
{
	/* disable clock gating and power gating */
	return hda_dsp_ctrl_clock_power_gating(sdev, false);
}