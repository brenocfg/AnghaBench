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
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct ff_packet_queue {TYPE_1__ flush_packet; int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_free_packet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_queue_flush (struct ff_packet_queue*) ; 
 int /*<<< orphan*/  pthread_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 

void packet_queue_free(struct ff_packet_queue *q)
{
	packet_queue_flush(q);

	pthread_mutex_destroy(&q->mutex);
	pthread_cond_destroy(&q->cond);

	av_free_packet(&q->flush_packet.base);
}