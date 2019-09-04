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
struct fw_iso_context {int dummy; } ;
struct amdtp_stream {int packet_index; unsigned int max_payload_length; scalar_t__ (* handle_packet ) (struct amdtp_stream*,unsigned int,int /*<<< orphan*/ ,unsigned int) ;int /*<<< orphan*/  context; int /*<<< orphan*/  pcm_buffer_pointer; TYPE_1__* unit; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 size_t IN_PACKET_HEADER_SIZE ; 
 unsigned int ISO_DATA_LENGTH_SHIFT ; 
 int /*<<< orphan*/  SNDRV_PCM_POS_XRUN ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdtp_stream_pcm_abort (struct amdtp_stream*) ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_cycle_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrement_cycle_count (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fw_iso_context_queue_flush (int /*<<< orphan*/ ) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  increment_cycle_count (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct amdtp_stream*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void in_stream_callback(struct fw_iso_context *context, u32 tstamp,
			       size_t header_length, void *header,
			       void *private_data)
{
	struct amdtp_stream *s = private_data;
	unsigned int i, packets;
	unsigned int payload_length, max_payload_length;
	__be32 *headers = header;
	u32 cycle;

	if (s->packet_index < 0)
		return;

	/* The number of packets in buffer */
	packets = header_length / IN_PACKET_HEADER_SIZE;

	cycle = compute_cycle_count(tstamp);

	/* Align to actual cycle count for the last packet. */
	cycle = decrement_cycle_count(cycle, packets);

	/* For buffer-over-run prevention. */
	max_payload_length = s->max_payload_length;

	for (i = 0; i < packets; i++) {
		cycle = increment_cycle_count(cycle, 1);

		/* The number of bytes in this packet */
		payload_length =
			(be32_to_cpu(headers[i]) >> ISO_DATA_LENGTH_SHIFT);
		if (payload_length > max_payload_length) {
			dev_err(&s->unit->device,
				"Detect jumbo payload: %04x %04x\n",
				payload_length, max_payload_length);
			break;
		}

		if (s->handle_packet(s, payload_length, cycle, i) < 0)
			break;
	}

	/* Queueing error or detecting invalid payload. */
	if (i < packets) {
		s->packet_index = -1;
		if (in_interrupt())
			amdtp_stream_pcm_abort(s);
		WRITE_ONCE(s->pcm_buffer_pointer, SNDRV_PCM_POS_XRUN);
		return;
	}

	fw_iso_context_queue_flush(s->context);
}