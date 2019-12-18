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
struct snd_pcm_runtime {int /*<<< orphan*/  hw; } ;
struct snd_hal2 {int /*<<< orphan*/  dac; } ;

/* Variables and functions */
 int hal2_alloc_dmabuf (struct snd_hal2*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hal2_pcm_hw ; 
 struct snd_hal2* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int hal2_playback_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_hal2 *hal2 = snd_pcm_substream_chip(substream);
	int err;

	runtime->hw = hal2_pcm_hw;

	err = hal2_alloc_dmabuf(hal2, &hal2->dac);
	if (err)
		return err;
	return 0;
}