#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {int dummy; } ;
struct TYPE_4__ {TYPE_1__* packets; } ;
struct amdtp_stream {size_t packet_index; unsigned int (* process_data_blocks ) (struct amdtp_stream*,int /*<<< orphan*/ *,unsigned int,unsigned int*) ;unsigned int data_block_counter; unsigned int data_block_quadlets; int /*<<< orphan*/  pcm; TYPE_2__ buffer; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int EIO ; 
 struct snd_pcm_substream* READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned int calculate_data_blocks (struct amdtp_stream*,unsigned int) ; 
 unsigned int calculate_syt (struct amdtp_stream*,unsigned int) ; 
 scalar_t__ queue_out_packet (struct amdtp_stream*,unsigned int) ; 
 unsigned int stub1 (struct amdtp_stream*,int /*<<< orphan*/ *,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  trace_out_packet_without_header (struct amdtp_stream*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  update_pcm_pointers (struct amdtp_stream*,struct snd_pcm_substream*,unsigned int) ; 

__attribute__((used)) static int handle_out_packet_without_header(struct amdtp_stream *s,
			unsigned int payload_length, unsigned int cycle,
			unsigned int index)
{
	__be32 *buffer;
	unsigned int syt;
	unsigned int data_blocks;
	unsigned int pcm_frames;
	struct snd_pcm_substream *pcm;

	buffer = s->buffer.packets[s->packet_index].buffer;
	syt = calculate_syt(s, cycle);
	data_blocks = calculate_data_blocks(s, syt);
	pcm_frames = s->process_data_blocks(s, buffer, data_blocks, &syt);
	s->data_block_counter = (s->data_block_counter + data_blocks) & 0xff;

	payload_length = data_blocks * 4 * s->data_block_quadlets;

	trace_out_packet_without_header(s, cycle, payload_length, data_blocks,
					index);

	if (queue_out_packet(s, payload_length) < 0)
		return -EIO;

	pcm = READ_ONCE(s->pcm);
	if (pcm && pcm_frames > 0)
		update_pcm_pointers(s, pcm, pcm_frames);

	/* No need to return the number of handled data blocks. */
	return 0;
}