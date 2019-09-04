#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct psc_dma_stream {int period_current; int /*<<< orphan*/  stream; scalar_t__ active; TYPE_2__* psc_dma; int /*<<< orphan*/  period_count; TYPE_1__* runtime; int /*<<< orphan*/  bcom_task; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int periods; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ bcom_buffer_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcom_retrieve_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  psc_dma_bcom_enqueue_next_buffer (struct psc_dma_stream*) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t psc_dma_bcom_irq(int irq, void *_psc_dma_stream)
{
	struct psc_dma_stream *s = _psc_dma_stream;

	spin_lock(&s->psc_dma->lock);
	/* For each finished period, dequeue the completed period buffer
	 * and enqueue a new one in it's place. */
	while (bcom_buffer_done(s->bcom_task)) {
		bcom_retrieve_buffer(s->bcom_task, NULL, NULL);

		s->period_current = (s->period_current+1) % s->runtime->periods;
		s->period_count++;

		psc_dma_bcom_enqueue_next_buffer(s);
	}
	spin_unlock(&s->psc_dma->lock);

	/* If the stream is active, then also inform the PCM middle layer
	 * of the period finished event. */
	if (s->active)
		snd_pcm_period_elapsed(s->stream);

	return IRQ_HANDLED;
}