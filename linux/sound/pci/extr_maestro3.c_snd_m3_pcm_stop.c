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
struct snd_pcm_substream {int stream; } ;
struct snd_m3 {int /*<<< orphan*/  dacs_active; } ;
struct TYPE_2__ {scalar_t__ data; } ;
struct m3_dma {TYPE_1__ inst; } ;

/* Variables and functions */
 scalar_t__ CDATA_INSTANCE_READY ; 
 int EINVAL ; 
 scalar_t__ KDATA_ADC1_REQUEST ; 
 scalar_t__ KDATA_MIXER_TASK_NUMBER ; 
 int /*<<< orphan*/  MEMTYPE_INTERNAL_DATA ; 
#define  SNDRV_PCM_STREAM_CAPTURE 129 
#define  SNDRV_PCM_STREAM_PLAYBACK 128 
 int /*<<< orphan*/  snd_m3_assp_write (struct snd_m3*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_m3_dec_timer_users (struct snd_m3*) ; 

__attribute__((used)) static int snd_m3_pcm_stop(struct snd_m3 *chip, struct m3_dma *s,
			   struct snd_pcm_substream *subs)
{
	if (! s || ! subs)
		return -EINVAL;

	snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
			  s->inst.data + CDATA_INSTANCE_READY, 0);
	snd_m3_dec_timer_users(chip);
	switch (subs->stream) {
	case SNDRV_PCM_STREAM_PLAYBACK:
		chip->dacs_active--;
		snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
				  KDATA_MIXER_TASK_NUMBER, 
				  chip->dacs_active);
		break;
	case SNDRV_PCM_STREAM_CAPTURE:
		snd_m3_assp_write(chip, MEMTYPE_INTERNAL_DATA,
				  KDATA_ADC1_REQUEST, 0);
		break;
	}
	return 0;
}