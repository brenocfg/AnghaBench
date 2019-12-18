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
struct voice {TYPE_1__* timing; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct voice* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct sis7019 {int /*<<< orphan*/  voice_lock; } ;
struct TYPE_2__ {struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_1__* __sis_alloc_playback_voice (struct sis7019*) ; 
 int /*<<< orphan*/  __sis_map_silence (struct sis7019*) ; 
 unsigned int params_buffer_size (struct snd_pcm_hw_params*) ; 
 unsigned int params_period_size (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  sis_free_voice (struct sis7019*,struct voice*) ; 
 struct sis7019* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sis_alloc_timing_voice(struct snd_pcm_substream *substream,
					struct snd_pcm_hw_params *hw_params)
{
	struct sis7019 *sis = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct voice *voice = runtime->private_data;
	unsigned int period_size, buffer_size;
	unsigned long flags;
	int needed;

	/* If there are one or two periods per buffer, we don't need a
	 * timing voice, as we can use the capture channel's interrupts
	 * to clock out the periods.
	 */
	period_size = params_period_size(hw_params);
	buffer_size = params_buffer_size(hw_params);
	needed = (period_size != buffer_size &&
			period_size != (buffer_size / 2));

	if (needed && !voice->timing) {
		spin_lock_irqsave(&sis->voice_lock, flags);
		voice->timing = __sis_alloc_playback_voice(sis);
		if (voice->timing)
			__sis_map_silence(sis);
		spin_unlock_irqrestore(&sis->voice_lock, flags);
		if (!voice->timing)
			return -ENOMEM;
		voice->timing->substream = substream;
	} else if (!needed && voice->timing) {
		sis_free_voice(sis, voice);
		voice->timing = NULL;
	}

	return 0;
}