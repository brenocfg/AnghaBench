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
struct snd_pcm_runtime {struct nuc900_audio* private_data; } ;
struct nuc900_audio {int /*<<< orphan*/  irq_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 

__attribute__((used)) static int nuc900_dma_close(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct nuc900_audio *nuc900_audio = runtime->private_data;

	free_irq(nuc900_audio->irq_num, substream);

	return 0;
}