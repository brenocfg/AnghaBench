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

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  aica_chn_halt () ; 
 int /*<<< orphan*/  spu_begin_dma (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_aicapcm_pcm_trigger(struct snd_pcm_substream
				   *substream, int cmd)
{
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		spu_begin_dma(substream);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		aica_chn_halt();
		break;
	default:
		return -EINVAL;
	}
	return 0;
}