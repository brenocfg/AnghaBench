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
struct xenvif_queue {int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_PUSH_RESPONSES_AND_CHECK_NOTIFY (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void push_tx_responses(struct xenvif_queue *queue)
{
	int notify;

	RING_PUSH_RESPONSES_AND_CHECK_NOTIFY(&queue->tx, notify);
	if (notify)
		notify_remote_via_irq(queue->tx_irq);
}