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
struct snd_soc_dai {int /*<<< orphan*/  dev; struct hdmi_codec_daifmt* playback_dma_data; } ;
struct hdmi_codec_daifmt {int bit_clk_master; int frame_clk_master; int frame_clk_inv; int bit_clk_inv; int /*<<< orphan*/  fmt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HDMI_AC97 ; 
 int /*<<< orphan*/  HDMI_DSP_A ; 
 int /*<<< orphan*/  HDMI_DSP_B ; 
 int /*<<< orphan*/  HDMI_I2S ; 
 int /*<<< orphan*/  HDMI_LEFT_J ; 
 int /*<<< orphan*/  HDMI_RIGHT_J ; 
#define  SND_SOC_DAIFMT_AC97 141 
#define  SND_SOC_DAIFMT_CBM_CFM 140 
#define  SND_SOC_DAIFMT_CBM_CFS 139 
#define  SND_SOC_DAIFMT_CBS_CFM 138 
#define  SND_SOC_DAIFMT_CBS_CFS 137 
#define  SND_SOC_DAIFMT_DSP_A 136 
#define  SND_SOC_DAIFMT_DSP_B 135 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 134 
#define  SND_SOC_DAIFMT_IB_IF 133 
#define  SND_SOC_DAIFMT_IB_NF 132 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
#define  SND_SOC_DAIFMT_LEFT_J 131 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_IF 130 
#define  SND_SOC_DAIFMT_NB_NF 129 
#define  SND_SOC_DAIFMT_RIGHT_J 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct hdmi_codec_daifmt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hdmi_codec_i2s_set_fmt(struct snd_soc_dai *dai,
				  unsigned int fmt)
{
	struct hdmi_codec_daifmt *cf = dai->playback_dma_data;

	/* Reset daifmt */
	memset(cf, 0, sizeof(*cf));

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		cf->bit_clk_master = 1;
		cf->frame_clk_master = 1;
		break;
	case SND_SOC_DAIFMT_CBS_CFM:
		cf->frame_clk_master = 1;
		break;
	case SND_SOC_DAIFMT_CBM_CFS:
		cf->bit_clk_master = 1;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		break;
	case SND_SOC_DAIFMT_NB_IF:
		cf->frame_clk_inv = 1;
		break;
	case SND_SOC_DAIFMT_IB_NF:
		cf->bit_clk_inv = 1;
		break;
	case SND_SOC_DAIFMT_IB_IF:
		cf->frame_clk_inv = 1;
		cf->bit_clk_inv = 1;
		break;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		cf->fmt = HDMI_I2S;
		break;
	case SND_SOC_DAIFMT_DSP_A:
		cf->fmt = HDMI_DSP_A;
		break;
	case SND_SOC_DAIFMT_DSP_B:
		cf->fmt = HDMI_DSP_B;
		break;
	case SND_SOC_DAIFMT_RIGHT_J:
		cf->fmt = HDMI_RIGHT_J;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		cf->fmt = HDMI_LEFT_J;
		break;
	case SND_SOC_DAIFMT_AC97:
		cf->fmt = HDMI_AC97;
		break;
	default:
		dev_err(dai->dev, "Invalid DAI interface format\n");
		return -EINVAL;
	}

	return 0;
}