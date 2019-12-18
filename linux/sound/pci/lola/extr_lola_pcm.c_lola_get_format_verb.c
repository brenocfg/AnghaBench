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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct TYPE_2__ {int format; unsigned int channels; } ;

/* Variables and functions */
#define  SNDRV_PCM_FORMAT_FLOAT_LE 131 
#define  SNDRV_PCM_FORMAT_S16_LE 130 
#define  SNDRV_PCM_FORMAT_S24_LE 129 
#define  SNDRV_PCM_FORMAT_S32_LE 128 

__attribute__((used)) static unsigned int lola_get_format_verb(struct snd_pcm_substream *substream)
{
	unsigned int verb;

	switch (substream->runtime->format) {
	case SNDRV_PCM_FORMAT_S16_LE:
		verb = 0x00000000;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
		verb = 0x00000200;
		break;
	case SNDRV_PCM_FORMAT_S32_LE:
		verb = 0x00000300;
		break;
	case SNDRV_PCM_FORMAT_FLOAT_LE:
		verb = 0x00001300;
		break;
	default:
		return 0;
	}
	verb |= substream->runtime->channels;
	return verb;
}