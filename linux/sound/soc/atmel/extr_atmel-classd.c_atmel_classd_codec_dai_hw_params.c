#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct atmel_classd {int /*<<< orphan*/  gclk; } ;
struct TYPE_3__ {int dsp_clk; int sample_rate; int /*<<< orphan*/  gclk_rate; scalar_t__ rate; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CLASSD_INTPMR ; 
 int CLASSD_INTPMR_DSP_CLK_FREQ_MASK ; 
 int CLASSD_INTPMR_DSP_CLK_FREQ_SHIFT ; 
 int CLASSD_INTPMR_FRAME_MASK ; 
 int CLASSD_INTPMR_FRAME_SHIFT ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 TYPE_1__* sample_rates ; 
 struct atmel_classd* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
atmel_classd_codec_dai_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *params,
			    struct snd_soc_dai *codec_dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct atmel_classd *dd = snd_soc_card_get_drvdata(rtd->card);
	struct snd_soc_component *component = codec_dai->component;
	int fs;
	int i, best, best_val, cur_val, ret;
	u32 mask, val;

	fs = params_rate(params);

	best = 0;
	best_val = abs(fs - sample_rates[0].rate);
	for (i = 1; i < ARRAY_SIZE(sample_rates); i++) {
		/* Closest match */
		cur_val = abs(fs - sample_rates[i].rate);
		if (cur_val < best_val) {
			best = i;
			best_val = cur_val;
		}
	}

	dev_dbg(component->dev,
		"Selected SAMPLE_RATE of %dHz, GCLK_RATE of %ldHz\n",
		sample_rates[best].rate, sample_rates[best].gclk_rate);

	clk_disable_unprepare(dd->gclk);

	ret = clk_set_rate(dd->gclk, sample_rates[best].gclk_rate);
	if (ret)
		return ret;

	mask = CLASSD_INTPMR_DSP_CLK_FREQ_MASK | CLASSD_INTPMR_FRAME_MASK;
	val = (sample_rates[best].dsp_clk << CLASSD_INTPMR_DSP_CLK_FREQ_SHIFT)
	| (sample_rates[best].sample_rate << CLASSD_INTPMR_FRAME_SHIFT);

	snd_soc_component_update_bits(component, CLASSD_INTPMR, mask, val);

	return clk_prepare_enable(dd->gclk);
}