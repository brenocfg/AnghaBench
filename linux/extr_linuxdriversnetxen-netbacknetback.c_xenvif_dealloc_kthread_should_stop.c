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
struct xenvif_queue {int /*<<< orphan*/  inflight_packets; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ kthread_should_stop () ; 

__attribute__((used)) static bool xenvif_dealloc_kthread_should_stop(struct xenvif_queue *queue)
{
	/* Dealloc thread must remain running until all inflight
	 * packets complete.
	 */
	return kthread_should_stop() &&
		!atomic_read(&queue->inflight_packets);
}