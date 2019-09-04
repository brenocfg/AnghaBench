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
struct amdtp_stream {int flags; int syt_interval; int data_block_quadlets; } ;

/* Variables and functions */
 int CIP_JUMBO_PAYLOAD ; 
 int CIP_NO_HEADER ; 

unsigned int amdtp_stream_get_max_payload(struct amdtp_stream *s)
{
	unsigned int multiplier = 1;
	unsigned int header_size = 0;

	if (s->flags & CIP_JUMBO_PAYLOAD)
		multiplier = 5;
	if (!(s->flags & CIP_NO_HEADER))
		header_size = 8;

	return header_size +
		s->syt_interval * s->data_block_quadlets * 4 * multiplier;
}