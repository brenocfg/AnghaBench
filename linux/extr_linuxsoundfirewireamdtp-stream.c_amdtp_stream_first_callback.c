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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* sc ) (struct fw_iso_context*,int /*<<< orphan*/ ,size_t,void*,struct amdtp_stream*) ;} ;
struct fw_iso_context {TYPE_1__ callback; } ;
struct amdtp_stream {int callbacked; scalar_t__ direction; int flags; int /*<<< orphan*/  start_cycle; int /*<<< orphan*/  handle_packet; int /*<<< orphan*/  callback_wait; } ;

/* Variables and functions */
 scalar_t__ AMDTP_IN_STREAM ; 
 int CIP_NO_HEADER ; 
 size_t IN_PACKET_HEADER_SIZE ; 
 scalar_t__ QUEUE_LENGTH ; 
 int /*<<< orphan*/  compute_cycle_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrement_cycle_count (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  handle_in_packet ; 
 int /*<<< orphan*/  handle_in_packet_without_header ; 
 int /*<<< orphan*/  handle_out_packet ; 
 int /*<<< orphan*/  handle_out_packet_without_header ; 
 int /*<<< orphan*/  in_stream_callback (struct fw_iso_context*,int /*<<< orphan*/ ,size_t,void*,struct amdtp_stream*) ; 
 int /*<<< orphan*/  increment_cycle_count (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  out_stream_callback (struct fw_iso_context*,int /*<<< orphan*/ ,size_t,void*,struct amdtp_stream*) ; 
 int /*<<< orphan*/  stub1 (struct fw_iso_context*,int /*<<< orphan*/ ,size_t,void*,struct amdtp_stream*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdtp_stream_first_callback(struct fw_iso_context *context,
					u32 tstamp, size_t header_length,
					void *header, void *private_data)
{
	struct amdtp_stream *s = private_data;
	u32 cycle;
	unsigned int packets;

	/*
	 * For in-stream, first packet has come.
	 * For out-stream, prepared to transmit first packet
	 */
	s->callbacked = true;
	wake_up(&s->callback_wait);

	cycle = compute_cycle_count(tstamp);

	if (s->direction == AMDTP_IN_STREAM) {
		packets = header_length / IN_PACKET_HEADER_SIZE;
		cycle = decrement_cycle_count(cycle, packets);
		context->callback.sc = in_stream_callback;
		if (s->flags & CIP_NO_HEADER)
			s->handle_packet = handle_in_packet_without_header;
		else
			s->handle_packet = handle_in_packet;
	} else {
		packets = header_length / 4;
		cycle = increment_cycle_count(cycle, QUEUE_LENGTH - packets);
		context->callback.sc = out_stream_callback;
		if (s->flags & CIP_NO_HEADER)
			s->handle_packet = handle_out_packet_without_header;
		else
			s->handle_packet = handle_out_packet;
	}

	s->start_cycle = cycle;

	context->callback.sc(context, tstamp, header_length, header, s);
}