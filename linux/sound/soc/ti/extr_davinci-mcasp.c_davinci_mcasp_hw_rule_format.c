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
typedef  int uint ;
struct snd_pcm_hw_rule {struct davinci_mcasp_ruledata* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_mask {int dummy; } ;
struct davinci_mcasp_ruledata {TYPE_1__* mcasp; } ;
struct TYPE_2__ {int tdm_slots; int auxclk_fs_ratio; unsigned int sysclk_freq; int slot_width; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MAX_RATE_ERROR_PPM ; 
 int SNDRV_PCM_FORMAT_LAST ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 scalar_t__ abs (int) ; 
 int davinci_mcasp_calc_clk_div (TYPE_1__*,unsigned int,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int) ; 
 struct snd_mask* hw_param_mask (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_mask_none (struct snd_mask*) ; 
 int snd_mask_refine (struct snd_mask*,struct snd_mask*) ; 
 int /*<<< orphan*/  snd_mask_set (struct snd_mask*,int) ; 
 scalar_t__ snd_mask_test (struct snd_mask*,int) ; 
 int snd_pcm_format_width (int) ; 

__attribute__((used)) static int davinci_mcasp_hw_rule_format(struct snd_pcm_hw_params *params,
					struct snd_pcm_hw_rule *rule)
{
	struct davinci_mcasp_ruledata *rd = rule->private;
	struct snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	struct snd_mask nfmt;
	int rate = params_rate(params);
	int slots = rd->mcasp->tdm_slots;
	int i, count = 0;

	snd_mask_none(&nfmt);

	for (i = 0; i <= SNDRV_PCM_FORMAT_LAST; i++) {
		if (snd_mask_test(fmt, i)) {
			uint sbits = snd_pcm_format_width(i);
			unsigned int sysclk_freq;
			int ppm;

			if (rd->mcasp->auxclk_fs_ratio)
				sysclk_freq =  rate *
					       rd->mcasp->auxclk_fs_ratio;
			else
				sysclk_freq = rd->mcasp->sysclk_freq;

			if (rd->mcasp->slot_width)
				sbits = rd->mcasp->slot_width;

			ppm = davinci_mcasp_calc_clk_div(rd->mcasp, sysclk_freq,
							 sbits * slots * rate,
							 false);
			if (abs(ppm) < DAVINCI_MAX_RATE_ERROR_PPM) {
				snd_mask_set(&nfmt, i);
				count++;
			}
		}
	}
	dev_dbg(rd->mcasp->dev,
		"%d possible sample format for %d Hz and %d tdm slots\n",
		count, rate, slots);

	return snd_mask_refine(fmt, &nfmt);
}