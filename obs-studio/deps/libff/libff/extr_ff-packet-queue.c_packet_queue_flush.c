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
struct ff_packet_queue {int /*<<< orphan*/  mutex; scalar_t__ total_size; scalar_t__ count; struct ff_packet_list* first_packet; int /*<<< orphan*/  last_packet; } ;
struct TYPE_2__ {int /*<<< orphan*/ * clock; int /*<<< orphan*/  base; } ;
struct ff_packet_list {TYPE_1__ packet; struct ff_packet_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_free_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (struct ff_packet_list**) ; 
 int /*<<< orphan*/  ff_clock_release (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void packet_queue_flush(struct ff_packet_queue *q)
{
	struct ff_packet_list *packet;

	pthread_mutex_lock(&q->mutex);

	for (packet = q->first_packet; packet != NULL;
	     packet = q->first_packet) {
		q->first_packet = packet->next;
		av_free_packet(&packet->packet.base);
		if (packet->packet.clock != NULL)
			ff_clock_release(&packet->packet.clock);
		av_freep(&packet);
	}

	q->last_packet = q->first_packet = NULL;
	q->count = 0;
	q->total_size = 0;

	pthread_mutex_unlock(&q->mutex);
}