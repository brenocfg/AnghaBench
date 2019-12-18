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
struct lapb_cb {int /*<<< orphan*/  ack_queue; int /*<<< orphan*/  write_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

void lapb_clear_queues(struct lapb_cb *lapb)
{
	skb_queue_purge(&lapb->write_queue);
	skb_queue_purge(&lapb->ack_queue);
}