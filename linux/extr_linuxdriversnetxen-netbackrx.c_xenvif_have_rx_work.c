#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xenvif_queue {TYPE_1__* vif; } ;
struct TYPE_2__ {scalar_t__ disabled; scalar_t__ stall_timeout; } ;

/* Variables and functions */
 scalar_t__ kthread_should_stop () ; 
 scalar_t__ xenvif_rx_queue_ready (struct xenvif_queue*) ; 
 scalar_t__ xenvif_rx_queue_stalled (struct xenvif_queue*) ; 
 scalar_t__ xenvif_rx_ring_slots_available (struct xenvif_queue*) ; 

__attribute__((used)) static bool xenvif_have_rx_work(struct xenvif_queue *queue)
{
	return xenvif_rx_ring_slots_available(queue) ||
		(queue->vif->stall_timeout &&
		 (xenvif_rx_queue_stalled(queue) ||
		  xenvif_rx_queue_ready(queue))) ||
		kthread_should_stop() ||
		queue->vif->disabled;
}