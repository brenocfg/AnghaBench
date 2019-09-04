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
struct ff_packet_queue {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; int /*<<< orphan*/  total_size; int /*<<< orphan*/  count; struct ff_packet_list* last_packet; struct ff_packet_list* first_packet; } ;
struct TYPE_2__ {scalar_t__ size; } ;
struct ff_packet {TYPE_1__ base; } ;
struct ff_packet_list {struct ff_packet packet; struct ff_packet_list* next; } ;

/* Variables and functions */
 int FF_PACKET_FAIL ; 
 int FF_PACKET_SUCCESS ; 
 struct ff_packet_list* av_malloc (int) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int packet_queue_put(struct ff_packet_queue *q, struct ff_packet *packet)
{
	struct ff_packet_list *new_packet;

	new_packet = av_malloc(sizeof(struct ff_packet_list));

	if (new_packet == NULL)
		return FF_PACKET_FAIL;

	new_packet->packet = *packet;
	new_packet->next = NULL;

	pthread_mutex_lock(&q->mutex);

	if (q->last_packet == NULL)
		q->first_packet = new_packet;
	else
		q->last_packet->next = new_packet;

	q->last_packet = new_packet;

	q->count++;
	q->total_size += new_packet->packet.base.size;

	pthread_cond_signal(&q->cond);
	pthread_mutex_unlock(&q->mutex);

	return FF_PACKET_SUCCESS;
}