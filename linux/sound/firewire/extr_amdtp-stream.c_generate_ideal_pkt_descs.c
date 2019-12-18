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
struct pkt_desc {unsigned int data_blocks; unsigned int data_block_counter; int /*<<< orphan*/  ctx_payload; int /*<<< orphan*/  syt; int /*<<< orphan*/  cycle; } ;
struct TYPE_4__ {TYPE_1__* packets; } ;
struct amdtp_stream {unsigned int data_block_counter; int packet_index; int flags; TYPE_2__ buffer; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int CIP_DBC_IS_END_EVENT ; 
 int QUEUE_LENGTH ; 
 unsigned int calculate_data_blocks (struct amdtp_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_syt (struct amdtp_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_it_cycle (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void generate_ideal_pkt_descs(struct amdtp_stream *s,
				     struct pkt_desc *descs,
				     const __be32 *ctx_header,
				     unsigned int packets)
{
	unsigned int dbc = s->data_block_counter;
	int i;

	for (i = 0; i < packets; ++i) {
		struct pkt_desc *desc = descs + i;
		unsigned int index = (s->packet_index + i) % QUEUE_LENGTH;

		desc->cycle = compute_it_cycle(*ctx_header);
		desc->syt = calculate_syt(s, desc->cycle);
		desc->data_blocks = calculate_data_blocks(s, desc->syt);

		if (s->flags & CIP_DBC_IS_END_EVENT)
			dbc = (dbc + desc->data_blocks) & 0xff;

		desc->data_block_counter = dbc;

		if (!(s->flags & CIP_DBC_IS_END_EVENT))
			dbc = (dbc + desc->data_blocks) & 0xff;

		desc->ctx_payload = s->buffer.packets[index].buffer;

		++ctx_header;
	}

	s->data_block_counter = dbc;
}