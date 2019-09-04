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
 int EBUSY ; 
 struct nuc900_audio* nuc900_ac97_data ; 
 int /*<<< orphan*/  nuc900_dma_interrupt ; 
 int /*<<< orphan*/  nuc900_pcm_hardware ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_soc_set_runtime_hwparams (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nuc900_dma_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct nuc900_audio *nuc900_audio;

	snd_soc_set_runtime_hwparams(substream, &nuc900_pcm_hardware);

	nuc900_audio = nuc900_ac97_data;

	if (request_irq(nuc900_audio->irq_num, nuc900_dma_interrupt,
			0, "nuc900-dma", substream))
		return -EBUSY;

	runtime->private_data = nuc900_audio;

	return 0;
}