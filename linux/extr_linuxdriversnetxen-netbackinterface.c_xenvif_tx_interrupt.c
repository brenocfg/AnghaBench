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
struct xenvif_queue {int /*<<< orphan*/  napi; int /*<<< orphan*/  tx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ RING_HAS_UNCONSUMED_REQUESTS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t xenvif_tx_interrupt(int irq, void *dev_id)
{
	struct xenvif_queue *queue = dev_id;

	if (RING_HAS_UNCONSUMED_REQUESTS(&queue->tx))
		napi_schedule(&queue->napi);

	return IRQ_HANDLED;
}