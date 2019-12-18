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
struct audio_stream {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  au1000_dma_start (struct audio_stream*) ; 
 int /*<<< orphan*/  au1000_dma_stop (struct audio_stream*) ; 
 struct audio_stream* ss_to_as (struct snd_pcm_substream*) ; 

__attribute__((used)) static int alchemy_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct audio_stream *stream = ss_to_as(substream);
	int err = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		au1000_dma_start(stream);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		au1000_dma_stop(stream);
		break;
	default:
		err = -EINVAL;
		break;
	}
	return err;
}