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
struct snd_pcm_substream {struct aaci* private_data; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int rate; } ;
struct aaci {int /*<<< orphan*/  ac97; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_EXTENDED_STATUS ; 
 int /*<<< orphan*/  AC97_PCM_LR_ADC_RATE ; 
 int /*<<< orphan*/  AC97_PCM_MIC_ADC_RATE ; 
 int /*<<< orphan*/  AC97_REC_SEL ; 
 int /*<<< orphan*/  aaci_ac97_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aaci_pcm_prepare (struct snd_pcm_substream*) ; 

__attribute__((used)) static int aaci_pcm_capture_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct aaci *aaci = substream->private_data;

	aaci_pcm_prepare(substream);

	/* allow changing of sample rate */
	aaci_ac97_write(aaci->ac97, AC97_EXTENDED_STATUS, 0x0001); /* VRA */
	aaci_ac97_write(aaci->ac97, AC97_PCM_LR_ADC_RATE, runtime->rate);
	aaci_ac97_write(aaci->ac97, AC97_PCM_MIC_ADC_RATE, runtime->rate);

	/* Record select: Mic: 0, Aux: 3, Line: 4 */
	aaci_ac97_write(aaci->ac97, AC97_REC_SEL, 0x0404);

	return 0;
}