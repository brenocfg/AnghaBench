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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {void* private_data; } ;

/* Variables and functions */
 void* snd_soc_dai_get_dma_data (int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_soc_set_runtime_hwparams (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xtfpga_pcm_hardware ; 

__attribute__((used)) static int xtfpga_pcm_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	void *p;

	snd_soc_set_runtime_hwparams(substream, &xtfpga_pcm_hardware);
	p = snd_soc_dai_get_dma_data(rtd->cpu_dai, substream);
	runtime->private_data = p;

	return 0;
}