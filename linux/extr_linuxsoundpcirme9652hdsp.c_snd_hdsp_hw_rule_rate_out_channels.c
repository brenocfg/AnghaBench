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
struct snd_pcm_hw_rule {struct hdsp* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_interval {scalar_t__ min; int max; int integer; } ;
struct hdsp {scalar_t__ ss_out_channels; scalar_t__ qs_out_channels; scalar_t__ io_type; scalar_t__ ds_out_channels; } ;

/* Variables and functions */
 scalar_t__ H9632 ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int snd_interval_refine (struct snd_interval*,struct snd_interval*) ; 

__attribute__((used)) static int snd_hdsp_hw_rule_rate_out_channels(struct snd_pcm_hw_params *params,
					     struct snd_pcm_hw_rule *rule)
{
	struct hdsp *hdsp = rule->private;
	struct snd_interval *c = hw_param_interval(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	struct snd_interval *r = hw_param_interval(params, SNDRV_PCM_HW_PARAM_RATE);
	if (c->min >= hdsp->ss_out_channels) {
		struct snd_interval t = {
			.min = 32000,
			.max = 48000,
			.integer = 1,
		};
		return snd_interval_refine(r, &t);
	} else if (c->max <= hdsp->qs_out_channels && hdsp->io_type == H9632) {
		struct snd_interval t = {
			.min = 128000,
			.max = 192000,
			.integer = 1,
		};
		return snd_interval_refine(r, &t);
	} else if (c->max <= hdsp->ds_out_channels) {
		struct snd_interval t = {
			.min = 64000,
			.max = 96000,
			.integer = 1,
		};
		return snd_interval_refine(r, &t);
	}
	return 0;
}