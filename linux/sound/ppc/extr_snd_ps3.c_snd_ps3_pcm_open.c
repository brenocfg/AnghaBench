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
struct snd_ps3_card_info {int /*<<< orphan*/  start_delay; struct snd_pcm_substream* substream; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int PS3_AUDIO_FIFO_STAGE_SIZE ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_BYTES ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_step (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_ps3_card_info* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_ps3_mute (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ps3_pcm_hw ; 
 int /*<<< orphan*/  snd_ps3_start_delay ; 

__attribute__((used)) static int snd_ps3_pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_ps3_card_info *card = snd_pcm_substream_chip(substream);

	/* to retrieve substream/runtime in interrupt handler */
	card->substream = substream;

	runtime->hw = snd_ps3_pcm_hw;

	card->start_delay = snd_ps3_start_delay;

	/* mute off */
	snd_ps3_mute(0); /* this function sleep */

	snd_pcm_hw_constraint_step(runtime, 0, SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
				   PS3_AUDIO_FIFO_STAGE_SIZE * 4 * 2);
	return 0;
}