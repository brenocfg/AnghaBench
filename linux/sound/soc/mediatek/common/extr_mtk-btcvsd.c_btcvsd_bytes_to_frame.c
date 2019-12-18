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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ format; int channels; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_FORMAT_S32_LE ; 
 scalar_t__ SNDRV_PCM_FORMAT_U32_LE ; 

__attribute__((used)) static int btcvsd_bytes_to_frame(struct snd_pcm_substream *substream,
				 int bytes)
{
	int count = bytes;
	struct snd_pcm_runtime *runtime = substream->runtime;

	if (runtime->format == SNDRV_PCM_FORMAT_S32_LE ||
	    runtime->format == SNDRV_PCM_FORMAT_U32_LE)
		count = count >> 2;
	else
		count = count >> 1;

	count = count / runtime->channels;
	return count;
}