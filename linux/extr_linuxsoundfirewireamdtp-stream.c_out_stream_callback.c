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
typedef  int /*<<< orphan*/  u32 ;
struct fw_iso_context {int dummy; } ;
struct amdtp_stream {int packet_index; scalar_t__ (* handle_packet ) (struct amdtp_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ;int /*<<< orphan*/  context; int /*<<< orphan*/  pcm_buffer_pointer; } ;

/* Variables and functions */
 int QUEUE_LENGTH ; 
 int /*<<< orphan*/  SNDRV_PCM_POS_XRUN ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdtp_stream_pcm_abort (struct amdtp_stream*) ; 
 int /*<<< orphan*/  compute_cycle_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_iso_context_queue_flush (int /*<<< orphan*/ ) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  increment_cycle_count (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct amdtp_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void out_stream_callback(struct fw_iso_context *context, u32 tstamp,
				size_t header_length, void *header,
				void *private_data)
{
	struct amdtp_stream *s = private_data;
	unsigned int i, packets = header_length / 4;
	u32 cycle;

	if (s->packet_index < 0)
		return;

	cycle = compute_cycle_count(tstamp);

	/* Align to actual cycle count for the last packet. */
	cycle = increment_cycle_count(cycle, QUEUE_LENGTH - packets);

	for (i = 0; i < packets; ++i) {
		cycle = increment_cycle_count(cycle, 1);
		if (s->handle_packet(s, 0, cycle, i) < 0) {
			s->packet_index = -1;
			if (in_interrupt())
				amdtp_stream_pcm_abort(s);
			WRITE_ONCE(s->pcm_buffer_pointer, SNDRV_PCM_POS_XRUN);
			return;
		}
	}

	fw_iso_context_queue_flush(s->context);
}