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
struct snd_pcm_runtime {struct cs4281_dma* private_data; } ;
struct cs4281_dma {int dummy; } ;
struct cs4281 {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_cs4281_mode (struct cs4281*,struct cs4281_dma*,struct snd_pcm_runtime*,int /*<<< orphan*/ ,int) ; 
 struct cs4281* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_cs4281_playback_prepare(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct cs4281_dma *dma = runtime->private_data;
	struct cs4281 *chip = snd_pcm_substream_chip(substream);

	spin_lock_irq(&chip->reg_lock);
	snd_cs4281_mode(chip, dma, runtime, 0, 1);
	spin_unlock_irq(&chip->reg_lock);
	return 0;
}