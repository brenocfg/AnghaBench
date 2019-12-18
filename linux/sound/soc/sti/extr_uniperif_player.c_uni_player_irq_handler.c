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
struct uniperif {scalar_t__ state; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  substream; int /*<<< orphan*/  dev; scalar_t__ underflow_enabled; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 unsigned int GET_UNIPERIF_ITS (struct uniperif*) ; 
 unsigned int GET_UNIPERIF_STATUS_1_UNDERFLOW_DURATION (struct uniperif*) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SET_UNIPERIF_BIT_CONTROL_CLR_UNDERFLOW_DURATION (struct uniperif*) ; 
 int /*<<< orphan*/  SET_UNIPERIF_ITM_BCLR_DMA_ERROR (struct uniperif*) ; 
 int /*<<< orphan*/  SET_UNIPERIF_ITM_BCLR_FIFO_ERROR (struct uniperif*) ; 
 int /*<<< orphan*/  SET_UNIPERIF_ITS_BCLR (struct uniperif*,unsigned int) ; 
 unsigned int UNIPERIF_ITM_UNDERFLOW_REC_DONE_MASK (struct uniperif*) ; 
 unsigned int UNIPERIF_ITM_UNDERFLOW_REC_FAILED_MASK (struct uniperif*) ; 
 unsigned int UNIPERIF_ITS_DMA_ERROR_MASK (struct uniperif*) ; 
 unsigned int UNIPERIF_ITS_FIFO_ERROR_MASK (struct uniperif*) ; 
 scalar_t__ UNIPERIF_STATE_STARTED ; 
 scalar_t__ UNIPERIF_STATE_STOPPED ; 
 scalar_t__ UNIPERIF_STATE_UNDERFLOW ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snd_pcm_stop_xrun (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_stream_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_stream_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static irqreturn_t uni_player_irq_handler(int irq, void *dev_id)
{
	irqreturn_t ret = IRQ_NONE;
	struct uniperif *player = dev_id;
	unsigned int status;
	unsigned int tmp;

	spin_lock(&player->irq_lock);
	if (!player->substream)
		goto irq_spin_unlock;

	snd_pcm_stream_lock(player->substream);
	if (player->state == UNIPERIF_STATE_STOPPED)
		goto stream_unlock;

	/* Get interrupt status & clear them immediately */
	status = GET_UNIPERIF_ITS(player);
	SET_UNIPERIF_ITS_BCLR(player, status);

	/* Check for fifo error (underrun) */
	if (unlikely(status & UNIPERIF_ITS_FIFO_ERROR_MASK(player))) {
		dev_err(player->dev, "FIFO underflow error detected\n");

		/* Interrupt is just for information when underflow recovery */
		if (player->underflow_enabled) {
			/* Update state to underflow */
			player->state = UNIPERIF_STATE_UNDERFLOW;

		} else {
			/* Disable interrupt so doesn't continually fire */
			SET_UNIPERIF_ITM_BCLR_FIFO_ERROR(player);

			/* Stop the player */
			snd_pcm_stop_xrun(player->substream);
		}

		ret = IRQ_HANDLED;
	}

	/* Check for dma error (overrun) */
	if (unlikely(status & UNIPERIF_ITS_DMA_ERROR_MASK(player))) {
		dev_err(player->dev, "DMA error detected\n");

		/* Disable interrupt so doesn't continually fire */
		SET_UNIPERIF_ITM_BCLR_DMA_ERROR(player);

		/* Stop the player */
		snd_pcm_stop_xrun(player->substream);

		ret = IRQ_HANDLED;
	}

	/* Check for underflow recovery done */
	if (unlikely(status & UNIPERIF_ITM_UNDERFLOW_REC_DONE_MASK(player))) {
		if (!player->underflow_enabled) {
			dev_err(player->dev,
				"unexpected Underflow recovering\n");
			ret = -EPERM;
			goto stream_unlock;
		}
		/* Read the underflow recovery duration */
		tmp = GET_UNIPERIF_STATUS_1_UNDERFLOW_DURATION(player);
		dev_dbg(player->dev, "Underflow recovered (%d LR clocks max)\n",
			tmp);

		/* Clear the underflow recovery duration */
		SET_UNIPERIF_BIT_CONTROL_CLR_UNDERFLOW_DURATION(player);

		/* Update state to started */
		player->state = UNIPERIF_STATE_STARTED;

		ret = IRQ_HANDLED;
	}

	/* Check if underflow recovery failed */
	if (unlikely(status &
		     UNIPERIF_ITM_UNDERFLOW_REC_FAILED_MASK(player))) {
		dev_err(player->dev, "Underflow recovery failed\n");

		/* Stop the player */
		snd_pcm_stop_xrun(player->substream);

		ret = IRQ_HANDLED;
	}

stream_unlock:
	snd_pcm_stream_unlock(player->substream);
irq_spin_unlock:
	spin_unlock(&player->irq_lock);

	return ret;
}