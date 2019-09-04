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
struct xenvif_queue {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  xenvif_kick_thread (struct xenvif_queue*) ; 

__attribute__((used)) static irqreturn_t xenvif_rx_interrupt(int irq, void *dev_id)
{
	struct xenvif_queue *queue = dev_id;

	xenvif_kick_thread(queue);

	return IRQ_HANDLED;
}