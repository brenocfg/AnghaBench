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
struct snd_pcm_hw_rule {int /*<<< orphan*/ * deps; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_mask {int dummy; } ;
struct snd_interval {unsigned int min; unsigned int max; } ;

/* Variables and functions */
 unsigned int SNDRV_PCM_FORMAT_LAST ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_FORMAT ; 
 struct snd_interval* hw_param_interval_c (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 struct snd_mask* hw_param_mask (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mask_any (struct snd_mask*) ; 
 int snd_mask_refine (struct snd_mask*,struct snd_mask*) ; 
 int /*<<< orphan*/  snd_mask_reset (struct snd_mask*,unsigned int) ; 
 int /*<<< orphan*/  snd_mask_test (struct snd_mask*,unsigned int) ; 
 int snd_pcm_format_physical_width (unsigned int) ; 

__attribute__((used)) static int snd_pcm_hw_rule_format(struct snd_pcm_hw_params *params,
				  struct snd_pcm_hw_rule *rule)
{
	unsigned int k;
	const struct snd_interval *i =
				hw_param_interval_c(params, rule->deps[0]);
	struct snd_mask m;
	struct snd_mask *mask = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	snd_mask_any(&m);
	for (k = 0; k <= SNDRV_PCM_FORMAT_LAST; ++k) {
		int bits;
		if (! snd_mask_test(mask, k))
			continue;
		bits = snd_pcm_format_physical_width(k);
		if (bits <= 0)
			continue; /* ignore invalid formats */
		if ((unsigned)bits < i->min || (unsigned)bits > i->max)
			snd_mask_reset(&m, k);
	}
	return snd_mask_refine(mask, &m);
}