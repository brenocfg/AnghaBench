#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct snd_soc_dai {int id; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct cs42l73_private {TYPE_1__* config; } ;
struct TYPE_2__ {int spc; int mmcc; } ;

/* Variables and functions */
 int CS42L73_ASP ; 
 int /*<<< orphan*/  CS42L73_MMCC (int) ; 
 int CS42L73_MS_MASTER ; 
 int CS42L73_PCM_BIT_ORDER ; 
 int CS42L73_PCM_MODE0 ; 
 int CS42L73_PCM_MODE1 ; 
 int CS42L73_PCM_MODE_MASK ; 
 int /*<<< orphan*/  CS42L73_SPC (int) ; 
 int CS42L73_SPDIF_PCM ; 
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 132 
#define  SND_SOC_DAIFMT_CBS_CFS 131 
#define  SND_SOC_DAIFMT_DSP_A 130 
#define  SND_SOC_DAIFMT_DSP_B 129 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 128 
 unsigned int SND_SOC_DAIFMT_IB_IF ; 
 unsigned int SND_SOC_DAIFMT_IB_NF ; 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct cs42l73_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs42l73_set_dai_fmt(struct snd_soc_dai *codec_dai, unsigned int fmt)
{
	struct snd_soc_component *component = codec_dai->component;
	struct cs42l73_private *priv = snd_soc_component_get_drvdata(component);
	u8 id = codec_dai->id;
	unsigned int inv, format;
	u8 spc, mmcc;

	spc = snd_soc_component_read32(component, CS42L73_SPC(id));
	mmcc = snd_soc_component_read32(component, CS42L73_MMCC(id));

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		mmcc |= CS42L73_MS_MASTER;
		break;

	case SND_SOC_DAIFMT_CBS_CFS:
		mmcc &= ~CS42L73_MS_MASTER;
		break;

	default:
		return -EINVAL;
	}

	format = (fmt & SND_SOC_DAIFMT_FORMAT_MASK);
	inv = (fmt & SND_SOC_DAIFMT_INV_MASK);

	switch (format) {
	case SND_SOC_DAIFMT_I2S:
		spc &= ~CS42L73_SPDIF_PCM;
		break;
	case SND_SOC_DAIFMT_DSP_A:
	case SND_SOC_DAIFMT_DSP_B:
		if (mmcc & CS42L73_MS_MASTER) {
			dev_err(component->dev,
				"PCM format in slave mode only\n");
			return -EINVAL;
		}
		if (id == CS42L73_ASP) {
			dev_err(component->dev,
				"PCM format is not supported on ASP port\n");
			return -EINVAL;
		}
		spc |= CS42L73_SPDIF_PCM;
		break;
	default:
		return -EINVAL;
	}

	if (spc & CS42L73_SPDIF_PCM) {
		/* Clear PCM mode, clear PCM_BIT_ORDER bit for MSB->LSB */
		spc &= ~(CS42L73_PCM_MODE_MASK | CS42L73_PCM_BIT_ORDER);
		switch (format) {
		case SND_SOC_DAIFMT_DSP_B:
			if (inv == SND_SOC_DAIFMT_IB_IF)
				spc |= CS42L73_PCM_MODE0;
			if (inv == SND_SOC_DAIFMT_IB_NF)
				spc |= CS42L73_PCM_MODE1;
		break;
		case SND_SOC_DAIFMT_DSP_A:
			if (inv == SND_SOC_DAIFMT_IB_IF)
				spc |= CS42L73_PCM_MODE1;
			break;
		default:
			return -EINVAL;
		}
	}

	priv->config[id].spc = spc;
	priv->config[id].mmcc = mmcc;

	return 0;
}