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
struct snd_pcm_substream {int dummy; } ;
struct axg_fifo {int /*<<< orphan*/  map; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int FIFO_INT_COUNT_REPEAT ; 
 unsigned int FIFO_INT_MASK ; 
 int /*<<< orphan*/  FIFO_STATUS1 ; 
 int /*<<< orphan*/  IRQ_RETVAL (unsigned int) ; 
 unsigned int STATUS1_INT_STS (unsigned int) ; 
 int /*<<< orphan*/  axg_fifo_ack_irq (struct axg_fifo*,unsigned int) ; 
 struct axg_fifo* axg_fifo_data (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  axg_fifo_dev (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 

__attribute__((used)) static irqreturn_t axg_fifo_pcm_irq_block(int irq, void *dev_id)
{
	struct snd_pcm_substream *ss = dev_id;
	struct axg_fifo *fifo = axg_fifo_data(ss);
	unsigned int status;

	regmap_read(fifo->map, FIFO_STATUS1, &status);

	status = STATUS1_INT_STS(status) & FIFO_INT_MASK;
	if (status & FIFO_INT_COUNT_REPEAT)
		snd_pcm_period_elapsed(ss);
	else
		dev_dbg(axg_fifo_dev(ss), "unexpected irq - STS 0x%02x\n",
			status);

	/* Ack irqs */
	axg_fifo_ack_irq(fifo, status);

	return IRQ_RETVAL(status);
}