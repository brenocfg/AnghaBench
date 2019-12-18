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
 int HDA_DSP_ADSPCS_CPA_MASK (unsigned int) ; 
 int HDA_DSP_ADSPCS_CRST_MASK (unsigned int) ; 
 int HDA_DSP_ADSPCS_CSTALL_MASK (unsigned int) ; 
 int HDA_DSP_ADSPCS_SPA_MASK (unsigned int) ; 
 int /*<<< orphan*/  HDA_DSP_BAR ; 
 int /*<<< orphan*/  HDA_DSP_REG_ADSPCS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int snd_sof_dsp_read (struct snd_sof_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool hda_dsp_core_is_enabled(struct snd_sof_dev *sdev,
			     unsigned int core_mask)
{
	int val;
	bool is_enable;

	val = snd_sof_dsp_read(sdev, HDA_DSP_BAR, HDA_DSP_REG_ADSPCS);

	is_enable = ((val & HDA_DSP_ADSPCS_CPA_MASK(core_mask)) &&
			(val & HDA_DSP_ADSPCS_SPA_MASK(core_mask)) &&
			!(val & HDA_DSP_ADSPCS_CRST_MASK(core_mask)) &&
			!(val & HDA_DSP_ADSPCS_CSTALL_MASK(core_mask)));

	dev_dbg(sdev->dev, "DSP core(s) enabled? %d : core_mask %x\n",
		is_enable, core_mask);

	return is_enable;
}