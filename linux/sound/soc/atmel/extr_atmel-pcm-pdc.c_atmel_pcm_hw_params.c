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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  cpu_dai; } ;
struct snd_pcm_substream {int /*<<< orphan*/  dma_buffer; struct snd_soc_pcm_runtime* private_data; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {scalar_t__ dma_bytes; scalar_t__ dma_addr; struct atmel_runtime_data* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct atmel_runtime_data {int /*<<< orphan*/  period_size; TYPE_1__* params; scalar_t__ dma_buffer_end; scalar_t__ dma_buffer; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dma_intr_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  atmel_pcm_dma_irq ; 
 scalar_t__ params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_period_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_set_runtime_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 TYPE_1__* snd_soc_dai_get_dma_data (int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 

__attribute__((used)) static int atmel_pcm_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct atmel_runtime_data *prtd = runtime->private_data;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;

	/* this may get called several times by oss emulation
	 * with different params */

	snd_pcm_set_runtime_buffer(substream, &substream->dma_buffer);
	runtime->dma_bytes = params_buffer_bytes(params);

	prtd->params = snd_soc_dai_get_dma_data(rtd->cpu_dai, substream);
	prtd->params->dma_intr_handler = atmel_pcm_dma_irq;

	prtd->dma_buffer = runtime->dma_addr;
	prtd->dma_buffer_end = runtime->dma_addr + runtime->dma_bytes;
	prtd->period_size = params_period_bytes(params);

	pr_debug("atmel-pcm: "
		"hw_params: DMA for %s initialized "
		"(dma_bytes=%zu, period_size=%zu)\n",
		prtd->params->name,
		runtime->dma_bytes,
		prtd->period_size);
	return 0;
}