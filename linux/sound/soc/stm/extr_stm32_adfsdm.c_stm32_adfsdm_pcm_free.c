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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm {TYPE_1__* streams; } ;
struct TYPE_2__ {struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_free_for_all (struct snd_pcm*) ; 

__attribute__((used)) static void stm32_adfsdm_pcm_free(struct snd_pcm *pcm)
{
	struct snd_pcm_substream *substream;

	substream = pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream;
	if (substream)
		snd_pcm_lib_preallocate_free_for_all(pcm);
}