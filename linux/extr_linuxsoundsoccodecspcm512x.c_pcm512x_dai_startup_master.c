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
struct snd_ratnum {int num; int den_min; int den_max; int den_step; } ;
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct snd_pcm_hw_constraint_ratnums {int nrats; struct snd_ratnum* rats; } ;
struct pcm512x_priv {int /*<<< orphan*/  sclk; scalar_t__ pll_out; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FRAME_BITS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm512x_hw_rule_rate ; 
 int snd_pcm_hw_constraint_ratnums (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_pcm_hw_constraint_ratnums*) ; 
 int snd_pcm_hw_rule_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pcm512x_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct pcm512x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int pcm512x_dai_startup_master(struct snd_pcm_substream *substream,
				      struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);
	struct device *dev = dai->dev;
	struct snd_pcm_hw_constraint_ratnums *constraints_no_pll;
	struct snd_ratnum *rats_no_pll;

	if (IS_ERR(pcm512x->sclk)) {
		dev_err(dev, "Need SCLK for master mode: %ld\n",
			PTR_ERR(pcm512x->sclk));
		return PTR_ERR(pcm512x->sclk);
	}

	if (pcm512x->pll_out)
		return snd_pcm_hw_rule_add(substream->runtime, 0,
					   SNDRV_PCM_HW_PARAM_RATE,
					   pcm512x_hw_rule_rate,
					   pcm512x,
					   SNDRV_PCM_HW_PARAM_FRAME_BITS,
					   SNDRV_PCM_HW_PARAM_CHANNELS, -1);

	constraints_no_pll = devm_kzalloc(dev, sizeof(*constraints_no_pll),
					  GFP_KERNEL);
	if (!constraints_no_pll)
		return -ENOMEM;
	constraints_no_pll->nrats = 1;
	rats_no_pll = devm_kzalloc(dev, sizeof(*rats_no_pll), GFP_KERNEL);
	if (!rats_no_pll)
		return -ENOMEM;
	constraints_no_pll->rats = rats_no_pll;
	rats_no_pll->num = clk_get_rate(pcm512x->sclk) / 64;
	rats_no_pll->den_min = 1;
	rats_no_pll->den_max = 128;
	rats_no_pll->den_step = 1;

	return snd_pcm_hw_constraint_ratnums(substream->runtime, 0,
					     SNDRV_PCM_HW_PARAM_RATE,
					     constraints_no_pll);
}