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
struct snd_pcm_hw_rule {struct snd_bebob_stream_formation* private; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct snd_interval {int integer; int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct snd_bebob_stream_formation {scalar_t__ pcm; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 unsigned int SND_BEBOB_STRM_FMT_ENTRIES ; 
 int /*<<< orphan*/  UINT_MAX ; 
 struct snd_interval* hw_param_interval (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 struct snd_interval* hw_param_interval_c (struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * snd_bebob_rate_table ; 
 int snd_interval_refine (struct snd_interval*,struct snd_interval*) ; 
 int /*<<< orphan*/  snd_interval_test (struct snd_interval const*,scalar_t__) ; 

__attribute__((used)) static int
hw_rule_rate(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule)
{
	struct snd_bebob_stream_formation *formations = rule->private;
	struct snd_interval *r =
		hw_param_interval(params, SNDRV_PCM_HW_PARAM_RATE);
	const struct snd_interval *c =
		hw_param_interval_c(params, SNDRV_PCM_HW_PARAM_CHANNELS);
	struct snd_interval t = {
		.min = UINT_MAX, .max = 0, .integer = 1
	};
	unsigned int i;

	for (i = 0; i < SND_BEBOB_STRM_FMT_ENTRIES; i++) {
		/* entry is invalid */
		if (formations[i].pcm == 0)
			continue;

		if (!snd_interval_test(c, formations[i].pcm))
			continue;

		t.min = min(t.min, snd_bebob_rate_table[i]);
		t.max = max(t.max, snd_bebob_rate_table[i]);

	}
	return snd_interval_refine(r, &t);
}