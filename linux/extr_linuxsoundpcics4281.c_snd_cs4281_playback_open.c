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
struct snd_pcm_runtime {int /*<<< orphan*/  hw; struct cs4281_dma* private_data; } ;
struct cs4281_dma {int right_slot; scalar_t__ left_slot; struct snd_pcm_substream* substream; } ;
struct cs4281 {struct cs4281_dma* dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_cs4281_playback ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_msbits (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int,int) ; 
 struct cs4281* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_cs4281_playback_open(struct snd_pcm_substream *substream)
{
	struct cs4281 *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct cs4281_dma *dma;

	dma = &chip->dma[0];
	dma->substream = substream;
	dma->left_slot = 0;
	dma->right_slot = 1;
	runtime->private_data = dma;
	runtime->hw = snd_cs4281_playback;
	/* should be detected from the AC'97 layer, but it seems
	   that although CS4297A rev B reports 18-bit ADC resolution,
	   samples are 20-bit */
	snd_pcm_hw_constraint_msbits(runtime, 0, 32, 20);
	return 0;
}