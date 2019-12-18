#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct voice {int flags; struct snd_pcm_substream* substream; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_4__ {int /*<<< orphan*/  rates; } ;
struct snd_pcm_runtime {TYPE_2__ hw; struct voice* private_data; } ;
struct sis7019 {TYPE_1__** ac97; int /*<<< orphan*/  voice_lock; struct voice capture_voice; } ;
struct TYPE_3__ {int /*<<< orphan*/ * rates; } ;

/* Variables and functions */
 size_t AC97_RATES_ADC ; 
 int EAGAIN ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_SIZE ; 
 int VOICE_IN_USE ; 
 TYPE_2__ sis_capture_hw_info ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_minmax (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_pcm_limit_hw_rates (struct snd_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 struct sis7019* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sis_capture_open(struct snd_pcm_substream *substream)
{
	struct sis7019 *sis = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct voice *voice = &sis->capture_voice;
	unsigned long flags;

	/* FIXME: The driver only supports recording from one channel
	 * at the moment, but it could support more.
	 */
	spin_lock_irqsave(&sis->voice_lock, flags);
	if (voice->flags & VOICE_IN_USE)
		voice = NULL;
	else
		voice->flags |= VOICE_IN_USE;
	spin_unlock_irqrestore(&sis->voice_lock, flags);

	if (!voice)
		return -EAGAIN;

	voice->substream = substream;
	runtime->private_data = voice;
	runtime->hw = sis_capture_hw_info;
	runtime->hw.rates = sis->ac97[0]->rates[AC97_RATES_ADC];
	snd_pcm_limit_hw_rates(runtime);
	snd_pcm_hw_constraint_minmax(runtime, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
						9, 0xfff9);
	snd_pcm_hw_constraint_minmax(runtime, SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
						9, 0xfff9);
	snd_pcm_set_sync(substream);
	return 0;
}