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
struct snd_pcm_runtime {int /*<<< orphan*/  dma_addr; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct axg_fifo {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIFO_INIT_ADDR ; 
 struct axg_fifo* axg_fifo_data (struct snd_pcm_substream*) ; 
 int axg_fifo_pcm_hw_params (struct snd_pcm_substream*,struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int g12a_fifo_pcm_hw_params(struct snd_pcm_substream *ss,
				   struct snd_pcm_hw_params *params)
{
	struct axg_fifo *fifo = axg_fifo_data(ss);
	struct snd_pcm_runtime *runtime = ss->runtime;
	int ret;

	ret = axg_fifo_pcm_hw_params(ss, params);
	if (ret)
		return ret;

	/* Set the initial memory address of the DMA */
	regmap_write(fifo->map, FIFO_INIT_ADDR, runtime->dma_addr);

	return 0;
}