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
struct cs_etm_packet {int dummy; } ;
struct cs_etm_decoder {scalar_t__ packet_count; int head; struct cs_etm_packet* packet_buffer; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_BUFFER ; 

int cs_etm_decoder__get_packet(struct cs_etm_decoder *decoder,
			       struct cs_etm_packet *packet)
{
	if (!decoder || !packet)
		return -EINVAL;

	/* Nothing to do, might as well just return */
	if (decoder->packet_count == 0)
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
	decoder->head = (decoder->head + 1) & (MAX_BUFFER - 1);

	*packet = decoder->packet_buffer[decoder->head];

	decoder->packet_count--;

	return 1;
}