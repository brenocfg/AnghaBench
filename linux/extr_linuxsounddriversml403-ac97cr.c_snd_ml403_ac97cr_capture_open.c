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
struct snd_ml403_ac97cr {struct snd_pcm_substream* capture_substream; } ;

/* Variables and functions */
 int CR_FIFO_SIZE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 int /*<<< orphan*/  WORK_INFO ; 
 int /*<<< orphan*/  snd_ml403_ac97cr_capture ; 
 int /*<<< orphan*/  snd_pcm_hw_constraint_step (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct snd_ml403_ac97cr* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_ml403_ac97cr_capture_open(struct snd_pcm_substream *substream)
{
	struct snd_ml403_ac97cr *ml403_ac97cr;
	struct snd_pcm_runtime *runtime;

	ml403_ac97cr = snd_pcm_substream_chip(substream);
	runtime = substream->runtime;

	PDEBUG(WORK_INFO, "open(capture)\n");
	ml403_ac97cr->capture_substream = substream;
	runtime->hw = snd_ml403_ac97cr_capture;

	snd_pcm_hw_constraint_step(runtime, 0,
				   SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
				   CR_FIFO_SIZE / 2);
	return 0;
}