#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_6__ {void* rate_max; void* rate_min; } ;
struct snd_pcm_runtime {TYPE_3__ hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* open ) (struct snd_ice1712*,struct snd_pcm_substream*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;
struct snd_ice1712 {TYPE_2__ spdif; struct snd_pcm_substream* playback_pro_substream; } ;

/* Variables and functions */
 void* PRO_RATE_DEFAULT ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 int /*<<< orphan*/  hw_constraints_rates ; 
 scalar_t__ is_pro_rate_locked (struct snd_ice1712*) ; 
 TYPE_3__ snd_ice1712_playback_pro ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_list (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_msbits (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 struct snd_ice1712* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stub1 (struct snd_ice1712*,struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_ice1712_playback_pro_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);

	ice->playback_pro_substream = substream;
	runtime->hw = snd_ice1712_playback_pro;
	snd_pcm_set_sync(substream);
	snd_pcm_hw_constraint_msbits(runtime, 0, 32, 24);
	snd_pcm_hw_constraint_list(runtime, 0, SNDRV_PCM_HW_PARAM_RATE, &hw_constraints_rates);
	if (is_pro_rate_locked(ice)) {
		runtime->hw.rate_min = PRO_RATE_DEFAULT;
		runtime->hw.rate_max = PRO_RATE_DEFAULT;
	}

	if (ice->spdif.ops.open)
		ice->spdif.ops.open(ice, substream);

	return 0;
}