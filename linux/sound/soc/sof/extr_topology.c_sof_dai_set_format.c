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
struct sof_ipc_dai_config {int /*<<< orphan*/  format; } ;
struct snd_soc_tplg_hw_config {scalar_t__ bclk_master; scalar_t__ fsync_master; scalar_t__ invert_fsync; scalar_t__ invert_bclk; } ;

/* Variables and functions */
 scalar_t__ SND_SOC_TPLG_BCLK_CM ; 
 scalar_t__ SND_SOC_TPLG_FSYNC_CM ; 
 int /*<<< orphan*/  SOF_DAI_FMT_CBM_CFM ; 
 int /*<<< orphan*/  SOF_DAI_FMT_CBM_CFS ; 
 int /*<<< orphan*/  SOF_DAI_FMT_CBS_CFM ; 
 int /*<<< orphan*/  SOF_DAI_FMT_CBS_CFS ; 
 int /*<<< orphan*/  SOF_DAI_FMT_IB_IF ; 
 int /*<<< orphan*/  SOF_DAI_FMT_IB_NF ; 
 int /*<<< orphan*/  SOF_DAI_FMT_NB_IF ; 
 int /*<<< orphan*/  SOF_DAI_FMT_NB_NF ; 

__attribute__((used)) static void sof_dai_set_format(struct snd_soc_tplg_hw_config *hw_config,
			       struct sof_ipc_dai_config *config)
{
	/* clock directions wrt codec */
	if (hw_config->bclk_master == SND_SOC_TPLG_BCLK_CM) {
		/* codec is bclk master */
		if (hw_config->fsync_master == SND_SOC_TPLG_FSYNC_CM)
			config->format |= SOF_DAI_FMT_CBM_CFM;
		else
			config->format |= SOF_DAI_FMT_CBM_CFS;
	} else {
		/* codec is bclk slave */
		if (hw_config->fsync_master == SND_SOC_TPLG_FSYNC_CM)
			config->format |= SOF_DAI_FMT_CBS_CFM;
		else
			config->format |= SOF_DAI_FMT_CBS_CFS;
	}

	/* inverted clocks ? */
	if (hw_config->invert_bclk) {
		if (hw_config->invert_fsync)
			config->format |= SOF_DAI_FMT_IB_IF;
		else
			config->format |= SOF_DAI_FMT_IB_NF;
	} else {
		if (hw_config->invert_fsync)
			config->format |= SOF_DAI_FMT_NB_IF;
		else
			config->format |= SOF_DAI_FMT_NB_NF;
	}
}