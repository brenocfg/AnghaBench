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
struct voice {struct snd_pcm_substream* substream; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; struct voice* private_data; } ;
struct sis7019 {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_SIZE ; 
 struct voice* sis_alloc_playback_voice (struct sis7019*) ; 
 int /*<<< orphan*/  sis_playback_hw_info ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_minmax (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_pcm_set_sync (struct snd_pcm_substream*) ; 
 struct sis7019* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int sis_playback_open(struct snd_pcm_substream *substream)
{
	struct sis7019 *sis = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct voice *voice;

	voice = sis_alloc_playback_voice(sis);
	if (!voice)
		return -EAGAIN;

	voice->substream = substream;
	runtime->private_data = voice;
	runtime->hw = sis_playback_hw_info;
	snd_pcm_hw_constraint_minmax(runtime, SNDRV_PCM_HW_PARAM_PERIOD_SIZE,
						9, 0xfff9);
	snd_pcm_hw_constraint_minmax(runtime, SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
						9, 0xfff9);
	snd_pcm_set_sync(substream);
	return 0;
}