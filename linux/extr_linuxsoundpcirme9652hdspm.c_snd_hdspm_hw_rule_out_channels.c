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
struct snd_pcm_hw_rule {struct hdspm* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_interval {int dummy; } ;
struct hdspm {unsigned int qs_out_channels; unsigned int ds_out_channels; unsigned int ss_out_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int snd_interval_list (struct snd_interval*,int,unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_hdspm_hw_rule_out_channels(struct snd_pcm_hw_params *params,
				      struct snd_pcm_hw_rule *rule)
{
	unsigned int list[3];
	struct hdspm *hdspm = rule->private;
	struct snd_interval *c = hw_param_interval(params,
			SNDRV_PCM_HW_PARAM_CHANNELS);

	list[0] = hdspm->qs_out_channels;
	list[1] = hdspm->ds_out_channels;
	list[2] = hdspm->ss_out_channels;
	return snd_interval_list(c, 3, list, 0);
}