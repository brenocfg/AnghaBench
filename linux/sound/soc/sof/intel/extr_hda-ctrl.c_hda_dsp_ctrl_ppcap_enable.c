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
struct snd_sof_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_DSP_PP_BAR ; 
 int /*<<< orphan*/  SOF_HDA_PPCTL_GPROCEN ; 
 int /*<<< orphan*/  SOF_HDA_REG_PP_PPCTL ; 
 int /*<<< orphan*/  snd_sof_dsp_update_bits (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hda_dsp_ctrl_ppcap_enable(struct snd_sof_dev *sdev, bool enable)
{
	u32 val = enable ? SOF_HDA_PPCTL_GPROCEN : 0;

	snd_sof_dsp_update_bits(sdev, HDA_DSP_PP_BAR, SOF_HDA_REG_PP_PPCTL,
				SOF_HDA_PPCTL_GPROCEN, val);
}