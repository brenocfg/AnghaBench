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
struct pcm3060_priv {TYPE_1__* dai; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {unsigned int sclk_freq; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PCM3060_CLK1 130 
#define  PCM3060_CLK2 129 
#define  PCM3060_CLK_DEF 128 
 size_t PCM3060_DAI_ID_DAC ; 
 unsigned int PCM3060_REG67 ; 
 unsigned int PCM3060_REG72 ; 
 unsigned int PCM3060_REG_CSEL ; 
 int SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 struct pcm3060_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int pcm3060_set_sysclk(struct snd_soc_dai *dai, int clk_id,
			      unsigned int freq, int dir)
{
	struct snd_soc_component *comp = dai->component;
	struct pcm3060_priv *priv = snd_soc_component_get_drvdata(comp);
	unsigned int reg;
	unsigned int val;

	if (dir != SND_SOC_CLOCK_IN) {
		dev_err(comp->dev, "unsupported sysclock dir: %d\n", dir);
		return -EINVAL;
	}

	switch (clk_id) {
	case PCM3060_CLK_DEF:
		val = 0;
		break;

	case PCM3060_CLK1:
		val = (dai->id == PCM3060_DAI_ID_DAC ? PCM3060_REG_CSEL : 0);
		break;

	case PCM3060_CLK2:
		val = (dai->id == PCM3060_DAI_ID_DAC ? 0 : PCM3060_REG_CSEL);
		break;

	default:
		dev_err(comp->dev, "unsupported sysclock id: %d\n", clk_id);
		return -EINVAL;
	}

	if (dai->id == PCM3060_DAI_ID_DAC)
		reg = PCM3060_REG67;
	else
		reg = PCM3060_REG72;

	regmap_update_bits(priv->regmap, reg, PCM3060_REG_CSEL, val);

	priv->dai[dai->id].sclk_freq = freq;

	return 0;
}