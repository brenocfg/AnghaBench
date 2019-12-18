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
struct snd_pcm_hw_rule {struct davinci_mcasp_ruledata* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_mask {int dummy; } ;
struct davinci_mcasp_ruledata {TYPE_1__* mcasp; } ;
struct TYPE_2__ {int max_format_width; } ;

/* Variables and functions */
 int SNDRV_PCM_FORMAT_LAST ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 struct snd_mask* hw_param_mask (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mask_none (struct snd_mask*) ; 
 int snd_mask_refine (struct snd_mask*,struct snd_mask*) ; 
 int /*<<< orphan*/  snd_mask_set (struct snd_mask*,int) ; 
 scalar_t__ snd_mask_test (struct snd_mask*,int) ; 
 int snd_pcm_format_width (int) ; 

__attribute__((used)) static int davinci_mcasp_hw_rule_format_width(struct snd_pcm_hw_params *params,
					      struct snd_pcm_hw_rule *rule)
{
	struct davinci_mcasp_ruledata *rd = rule->private;
	struct snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	struct snd_mask nfmt;
	int i, format_width;

	snd_mask_none(&nfmt);
	format_width = rd->mcasp->max_format_width;

	for (i = 0; i <= SNDRV_PCM_FORMAT_LAST; i++) {
		if (snd_mask_test(fmt, i)) {
			if (snd_pcm_format_width(i) == format_width) {
				snd_mask_set(&nfmt, i);
			}
		}
	}

	return snd_mask_refine(fmt, &nfmt);
}