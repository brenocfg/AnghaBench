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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct device {int dummy; } ;
struct axg_fifo {int /*<<< orphan*/  pclk; int /*<<< orphan*/  arb; int /*<<< orphan*/  map; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXG_FIFO_MIN_DEPTH ; 
 int /*<<< orphan*/  CTRL0_INT_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTRL1_STATUS2_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTRL1_STATUS2_SEL_MASK ; 
 int /*<<< orphan*/  FIFO_CTRL0 ; 
 int /*<<< orphan*/  FIFO_CTRL1 ; 
 int /*<<< orphan*/  FIFO_INT_MASK ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_BUFFER_BYTES ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIOD_BYTES ; 
 int /*<<< orphan*/  STATUS2_SEL_DDR_READ ; 
 int /*<<< orphan*/  __dma_enable (struct axg_fifo*,int) ; 
 int /*<<< orphan*/  axg_fifo_ack_irq (struct axg_fifo*,int /*<<< orphan*/ ) ; 
 struct axg_fifo* axg_fifo_data (struct snd_pcm_substream*) ; 
 struct device* axg_fifo_dev (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  axg_fifo_hw ; 
 int /*<<< orphan*/  axg_fifo_pcm_irq_block ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int snd_pcm_hw_constraint_step (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_set_runtime_hwparams (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int axg_fifo_pcm_open(struct snd_pcm_substream *ss)
{
	struct axg_fifo *fifo = axg_fifo_data(ss);
	struct device *dev = axg_fifo_dev(ss);
	int ret;

	snd_soc_set_runtime_hwparams(ss, &axg_fifo_hw);

	/*
	 * Make sure the buffer and period size are multiple of the FIFO
	 * minimum depth size
	 */
	ret = snd_pcm_hw_constraint_step(ss->runtime, 0,
					 SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
					 AXG_FIFO_MIN_DEPTH);
	if (ret)
		return ret;

	ret = snd_pcm_hw_constraint_step(ss->runtime, 0,
					 SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
					 AXG_FIFO_MIN_DEPTH);
	if (ret)
		return ret;

	ret = request_irq(fifo->irq, axg_fifo_pcm_irq_block, 0,
			  dev_name(dev), ss);
	if (ret)
		return ret;

	/* Enable pclk to access registers and clock the fifo ip */
	ret = clk_prepare_enable(fifo->pclk);
	if (ret)
		return ret;

	/* Setup status2 so it reports the memory pointer */
	regmap_update_bits(fifo->map, FIFO_CTRL1,
			   CTRL1_STATUS2_SEL_MASK,
			   CTRL1_STATUS2_SEL(STATUS2_SEL_DDR_READ));

	/* Make sure the dma is initially disabled */
	__dma_enable(fifo, false);

	/* Disable irqs until params are ready */
	regmap_update_bits(fifo->map, FIFO_CTRL0,
			   CTRL0_INT_EN(FIFO_INT_MASK), 0);

	/* Clear any pending interrupt */
	axg_fifo_ack_irq(fifo, FIFO_INT_MASK);

	/* Take memory arbitror out of reset */
	ret = reset_control_deassert(fifo->arb);
	if (ret)
		clk_disable_unprepare(fifo->pclk);

	return ret;
}