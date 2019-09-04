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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; TYPE_1__* codec_dai; } ;
struct snd_soc_component {int dummy; } ;
struct snd_ratnum {int num; int den_min; int den_max; int den_step; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {unsigned int rate_num; unsigned int rate_den; } ;
struct pcm512x_priv {int /*<<< orphan*/  sclk; } ;
struct TYPE_2__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct snd_ratnum*) ; 
 struct snd_ratnum* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int snd_interval_ratnum (int /*<<< orphan*/ ,int,struct snd_ratnum*,unsigned int*,unsigned int*) ; 
 struct pcm512x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int snd_allo_boss_update_rate_den(
	struct snd_pcm_substream *substream, struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_component *component = rtd->codec_dai->component;
	struct pcm512x_priv *pcm512x = snd_soc_component_get_drvdata(component);
	struct snd_ratnum *rats_no_pll;
	unsigned int num = 0, den = 0;
	int err;

	rats_no_pll = devm_kzalloc(rtd->dev, sizeof(*rats_no_pll), GFP_KERNEL);
	if (!rats_no_pll)
		return -ENOMEM;

	rats_no_pll->num = clk_get_rate(pcm512x->sclk) / 64;
	rats_no_pll->den_min = 1;
	rats_no_pll->den_max = 128;
	rats_no_pll->den_step = 1;

	err = snd_interval_ratnum(hw_param_interval(params,
		SNDRV_PCM_HW_PARAM_RATE), 1, rats_no_pll, &num, &den);
	if (err >= 0 && den) {
		params->rate_num = num;
		params->rate_den = den;
	}

	devm_kfree(rtd->dev, rats_no_pll);
	return 0;
}