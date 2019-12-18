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
struct snd_soc_dai {size_t id; struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct pcm3060_priv {int /*<<< orphan*/  regmap; TYPE_1__* dai; } ;
struct TYPE_2__ {unsigned int sclk_freq; int /*<<< orphan*/  is_master; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t PCM3060_DAI_ID_DAC ; 
 unsigned int PCM3060_REG67 ; 
 unsigned int PCM3060_REG72 ; 
 int /*<<< orphan*/  PCM3060_REG_MASK_MS ; 
 unsigned int PCM3060_REG_MS_M128 ; 
 unsigned int PCM3060_REG_MS_M192 ; 
 unsigned int PCM3060_REG_MS_M256 ; 
 unsigned int PCM3060_REG_MS_M384 ; 
 unsigned int PCM3060_REG_MS_M512 ; 
 unsigned int PCM3060_REG_MS_M768 ; 
 unsigned int PCM3060_REG_MS_S ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 struct pcm3060_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int pcm3060_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct snd_soc_component *comp = dai->component;
	struct pcm3060_priv *priv = snd_soc_component_get_drvdata(comp);
	unsigned int rate;
	unsigned int ratio;
	unsigned int reg;
	unsigned int val;

	if (!priv->dai[dai->id].is_master) {
		val = PCM3060_REG_MS_S;
		goto val_ready;
	}

	rate = params_rate(params);
	if (!rate) {
		dev_err(comp->dev, "rate is not configured\n");
		return -EINVAL;
	}

	ratio = priv->dai[dai->id].sclk_freq / rate;

	switch (ratio) {
	case 768:
		val = PCM3060_REG_MS_M768;
		break;
	case 512:
		val = PCM3060_REG_MS_M512;
		break;
	case 384:
		val = PCM3060_REG_MS_M384;
		break;
	case 256:
		val = PCM3060_REG_MS_M256;
		break;
	case 192:
		val = PCM3060_REG_MS_M192;
		break;
	case 128:
		val = PCM3060_REG_MS_M128;
		break;
	default:
		dev_err(comp->dev, "unsupported ratio: %d\n", ratio);
		return -EINVAL;
	}

val_ready:
	if (dai->id == PCM3060_DAI_ID_DAC)
		reg = PCM3060_REG67;
	else
		reg = PCM3060_REG72;

	regmap_update_bits(priv->regmap, reg, PCM3060_REG_MASK_MS, val);

	return 0;
}