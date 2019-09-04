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
struct uniperif {scalar_t__ state; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  substream; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int GET_UNIPERIF_ITS (struct uniperif*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SET_UNIPERIF_ITS_BCLR (struct uniperif*,unsigned int) ; 
 unsigned int UNIPERIF_ITS_FIFO_ERROR_MASK (struct uniperif*) ; 
 scalar_t__ UNIPERIF_STATE_STOPPED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_pcm_stop_xrun (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static irqreturn_t uni_reader_irq_handler(int irq, void *dev_id)
{
	irqreturn_t ret = IRQ_NONE;
	struct uniperif *reader = dev_id;
	unsigned int status;

	spin_lock(&reader->irq_lock);
	if (!reader->substream)
		goto irq_spin_unlock;

	snd_pcm_stream_lock(reader->substream);
	if (reader->state == UNIPERIF_STATE_STOPPED) {
		/* Unexpected IRQ: do nothing */
		dev_warn(reader->dev, "unexpected IRQ\n");
		goto stream_unlock;
	}

	/* Get interrupt status & clear them immediately */
	status = GET_UNIPERIF_ITS(reader);
	SET_UNIPERIF_ITS_BCLR(reader, status);

	/* Check for fifo overflow error */
	if (unlikely(status & UNIPERIF_ITS_FIFO_ERROR_MASK(reader))) {
		dev_err(reader->dev, "FIFO error detected\n");

		snd_pcm_stop_xrun(reader->substream);

		ret = IRQ_HANDLED;
	}

stream_unlock:
	snd_pcm_stream_unlock(reader->substream);
irq_spin_unlock:
	spin_unlock(&reader->irq_lock);

	return ret;
}