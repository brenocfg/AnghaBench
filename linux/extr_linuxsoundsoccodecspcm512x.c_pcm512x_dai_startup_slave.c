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
struct snd_soc_dai {struct device* dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct regmap {int dummy; } ;
struct pcm512x_priv {int /*<<< orphan*/  sclk; struct regmap* regmap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCM512x_ERROR_DETECT ; 
 int /*<<< orphan*/  PCM512x_IDCH ; 
 int /*<<< orphan*/  PCM512x_PLL_REF ; 
 int /*<<< orphan*/  PCM512x_SREF ; 
 int /*<<< orphan*/  PCM512x_SREF_BCK ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  constraints_slave ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_constraint_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct pcm512x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int pcm512x_dai_startup_slave(struct snd_pcm_substream *substream,
				     struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);
	struct device *dev = dai->dev;
	struct regmap *regmap = pcm512x->regmap;

	if (IS_ERR(pcm512x->sclk)) {
		dev_info(dev, "No SCLK, using BCLK: %ld\n",
			 PTR_ERR(pcm512x->sclk));

		/* Disable reporting of missing SCLK as an error */
		regmap_update_bits(regmap, PCM512x_ERROR_DETECT,
				   PCM512x_IDCH, PCM512x_IDCH);

		/* Switch PLL input to BCLK */
		regmap_update_bits(regmap, PCM512x_PLL_REF,
				   PCM512x_SREF, PCM512x_SREF_BCK);
	}

	return snd_pcm_hw_constraint_list(substream->runtime, 0,
					  SNDRV_PCM_HW_PARAM_RATE,
					  &constraints_slave);
}