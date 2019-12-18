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
struct snd_pcm_substream {int dummy; } ;
struct snd_hal2 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  hal2_start_adc (struct snd_hal2*) ; 
 int /*<<< orphan*/  hal2_stop_adc (struct snd_hal2*) ; 
 struct snd_hal2* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int hal2_capture_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_hal2 *hal2 = snd_pcm_substream_chip(substream);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		hal2_start_adc(hal2);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		hal2_stop_adc(hal2);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}