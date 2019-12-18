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
struct cs_etm_packet_queue {scalar_t__ packet_count; int head; struct cs_etm_packet* packet_buffer; } ;
struct cs_etm_packet {int dummy; } ;

/* Variables and functions */
 int CS_ETM_PACKET_MAX_BUFFER ; 
 int EINVAL ; 

int cs_etm_decoder__get_packet(struct cs_etm_packet_queue *packet_queue,
			       struct cs_etm_packet *packet)
{
	if (!packet_queue || !packet)
		return -EINVAL;

	/* Nothing to do, might as well just return */
	if (packet_queue->packet_count == 0)
		return 0;
	/*
	 * The queueing process in function cs_etm_decoder__buffer_packet()
	 * increments the tail *before* using it.  This is somewhat counter
	 * intuitive but it has the advantage of centralizing tail management
	 * at a single location.  Because of that we need to follow the same
	 * heuristic with the head, i.e we increment it before using its
	 * value.  Otherwise the first element of the packet queue is not
	 * used.
	 */
	packet_queue->head = (packet_queue->head + 1) &
			     (CS_ETM_PACKET_MAX_BUFFER - 1);

	*packet = packet_queue->packet_buffer[packet_queue->head];

	packet_queue->packet_count--;

	return 1;
}