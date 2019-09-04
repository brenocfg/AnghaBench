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
struct snd_soc_tplg_link_config {int num_hw_configs; scalar_t__ default_hw_config_id; struct snd_soc_tplg_hw_config* hw_config; } ;
struct snd_soc_tplg_hw_config {scalar_t__ id; int fmt; int clock_gated; unsigned char invert_bclk; unsigned char invert_fsync; scalar_t__ bclk_master; scalar_t__ fsync_master; } ;
struct snd_soc_dai_link {int dai_fmt; } ;

/* Variables and functions */
 int SND_SOC_DAIFMT_CBM_CFM ; 
 int SND_SOC_DAIFMT_CBM_CFS ; 
 int SND_SOC_DAIFMT_CBS_CFM ; 
 int SND_SOC_DAIFMT_CBS_CFS ; 
 int SND_SOC_DAIFMT_CONT ; 
 int SND_SOC_DAIFMT_FORMAT_MASK ; 
 int SND_SOC_DAIFMT_GATED ; 
 int SND_SOC_DAIFMT_IB_IF ; 
 int SND_SOC_DAIFMT_IB_NF ; 
 int SND_SOC_DAIFMT_NB_IF ; 
 int SND_SOC_DAIFMT_NB_NF ; 
 scalar_t__ SND_SOC_TPLG_BCLK_CM ; 
#define  SND_SOC_TPLG_DAI_CLK_GATE_CONT 129 
#define  SND_SOC_TPLG_DAI_CLK_GATE_GATED 128 
 scalar_t__ SND_SOC_TPLG_FSYNC_CM ; 

__attribute__((used)) static void set_link_hw_format(struct snd_soc_dai_link *link,
			struct snd_soc_tplg_link_config *cfg)
{
	struct snd_soc_tplg_hw_config *hw_config;
	unsigned char bclk_master, fsync_master;
	unsigned char invert_bclk, invert_fsync;
	int i;

	for (i = 0; i < cfg->num_hw_configs; i++) {
		hw_config = &cfg->hw_config[i];
		if (hw_config->id != cfg->default_hw_config_id)
			continue;

		link->dai_fmt = hw_config->fmt & SND_SOC_DAIFMT_FORMAT_MASK;

		/* clock gating */
		switch (hw_config->clock_gated) {
		case SND_SOC_TPLG_DAI_CLK_GATE_GATED:
			link->dai_fmt |= SND_SOC_DAIFMT_GATED;
			break;

		case SND_SOC_TPLG_DAI_CLK_GATE_CONT:
			link->dai_fmt |= SND_SOC_DAIFMT_CONT;
			break;

		default:
			/* ignore the value */
			break;
		}

		/* clock signal polarity */
		invert_bclk = hw_config->invert_bclk;
		invert_fsync = hw_config->invert_fsync;
		if (!invert_bclk && !invert_fsync)
			link->dai_fmt |= SND_SOC_DAIFMT_NB_NF;
		else if (!invert_bclk && invert_fsync)
			link->dai_fmt |= SND_SOC_DAIFMT_NB_IF;
		else if (invert_bclk && !invert_fsync)
			link->dai_fmt |= SND_SOC_DAIFMT_IB_NF;
		else
			link->dai_fmt |= SND_SOC_DAIFMT_IB_IF;

		/* clock masters */
		bclk_master = (hw_config->bclk_master ==
			       SND_SOC_TPLG_BCLK_CM);
		fsync_master = (hw_config->fsync_master ==
				SND_SOC_TPLG_FSYNC_CM);
		if (bclk_master && fsync_master)
			link->dai_fmt |= SND_SOC_DAIFMT_CBM_CFM;
		else if (!bclk_master && fsync_master)
			link->dai_fmt |= SND_SOC_DAIFMT_CBS_CFM;
		else if (bclk_master && !fsync_master)
			link->dai_fmt |= SND_SOC_DAIFMT_CBM_CFS;
		else
			link->dai_fmt |= SND_SOC_DAIFMT_CBS_CFS;
	}
}