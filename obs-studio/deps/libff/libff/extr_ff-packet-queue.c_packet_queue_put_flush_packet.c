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
struct ff_packet_queue {int /*<<< orphan*/  flush_packet; } ;

/* Variables and functions */
 int packet_queue_put (struct ff_packet_queue*,int /*<<< orphan*/ *) ; 

int packet_queue_put_flush_packet(struct ff_packet_queue *q)
{
	return packet_queue_put(q, &q->flush_packet);
}