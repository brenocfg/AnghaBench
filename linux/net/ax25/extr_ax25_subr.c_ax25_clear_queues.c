#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  frag_queue; int /*<<< orphan*/  reseq_queue; int /*<<< orphan*/  ack_queue; int /*<<< orphan*/  write_queue; } ;
typedef  TYPE_1__ ax25_cb ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

void ax25_clear_queues(ax25_cb *ax25)
{
	skb_queue_purge(&ax25->write_queue);
	skb_queue_purge(&ax25->ack_queue);
	skb_queue_purge(&ax25->reseq_queue);
	skb_queue_purge(&ax25->frag_queue);
}