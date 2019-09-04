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
struct snd_pcm_runtime {unsigned int dma_addr; unsigned int dma_bytes; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct axg_fifo {int /*<<< orphan*/  map; } ;
typedef  unsigned int dma_addr_t ;

/* Variables and functions */
 unsigned int AXG_FIFO_BURST ; 
 int /*<<< orphan*/  CTRL0_INT_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIFO_CTRL0 ; 
 int /*<<< orphan*/  FIFO_FINISH_ADDR ; 
 int /*<<< orphan*/  FIFO_INT_ADDR ; 
 int /*<<< orphan*/  FIFO_INT_COUNT_REPEAT ; 
 int /*<<< orphan*/  FIFO_START_ADDR ; 
 struct axg_fifo* axg_fifo_data (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 unsigned int params_period_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axg_fifo_pcm_hw_params(struct snd_pcm_substream *ss,
				  struct snd_pcm_hw_params *params)
{
	struct snd_pcm_runtime *runtime = ss->runtime;
	struct axg_fifo *fifo = axg_fifo_data(ss);
	dma_addr_t end_ptr;
	unsigned int burst_num;
	int ret;

	ret = snd_pcm_lib_malloc_pages(ss, params_buffer_bytes(params));
	if (ret < 0)
		return ret;

	/* Setup dma memory pointers */
	end_ptr = runtime->dma_addr + runtime->dma_bytes - AXG_FIFO_BURST;
	regmap_write(fifo->map, FIFO_START_ADDR, runtime->dma_addr);
	regmap_write(fifo->map, FIFO_FINISH_ADDR, end_ptr);

	/* Setup interrupt periodicity */
	burst_num = params_period_bytes(params) / AXG_FIFO_BURST;
	regmap_write(fifo->map, FIFO_INT_ADDR, burst_num);

	/* Enable block count irq */
	regmap_update_bits(fifo->map, FIFO_CTRL0,
			   CTRL0_INT_EN(FIFO_INT_COUNT_REPEAT),
			   CTRL0_INT_EN(FIFO_INT_COUNT_REPEAT));

	return 0;
}