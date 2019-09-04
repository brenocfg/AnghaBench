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
struct data_queue {int /*<<< orphan*/  qid; int /*<<< orphan*/  rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt2x00_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00queue_flush_queue (struct data_queue*,int) ; 
 int /*<<< orphan*/  rt2x00queue_start_queue (struct data_queue*) ; 
 int /*<<< orphan*/  rt2x00queue_stop_queue (struct data_queue*) ; 

__attribute__((used)) static void rt2x00usb_watchdog_tx_dma(struct data_queue *queue)
{
	rt2x00_warn(queue->rt2x00dev, "TX queue %d DMA timed out, invoke forced forced reset\n",
		    queue->qid);

	rt2x00queue_stop_queue(queue);
	rt2x00queue_flush_queue(queue, true);
	rt2x00queue_start_queue(queue);
}