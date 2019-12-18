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
struct fw_iso_packet {unsigned int payload_length; int header_length; scalar_t__ header; } ;
struct amdtp_stream {unsigned int data_block_quadlets; int flags; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int CIP_NO_HEADER ; 
 int /*<<< orphan*/  generate_cip_header (struct amdtp_stream*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  trace_amdtp_packet (struct amdtp_stream*,unsigned int,int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void build_it_pkt_header(struct amdtp_stream *s, unsigned int cycle,
				struct fw_iso_packet *params,
				unsigned int data_blocks,
				unsigned int data_block_counter,
				unsigned int syt, unsigned int index)
{
	unsigned int payload_length;
	__be32 *cip_header;

	payload_length = data_blocks * sizeof(__be32) * s->data_block_quadlets;
	params->payload_length = payload_length;

	if (!(s->flags & CIP_NO_HEADER)) {
		cip_header = (__be32 *)params->header;
		generate_cip_header(s, cip_header, data_block_counter, syt);
		params->header_length = 2 * sizeof(__be32);
		payload_length += params->header_length;
	} else {
		cip_header = NULL;
	}

	trace_amdtp_packet(s, cycle, cip_header, payload_length, data_blocks,
			   data_block_counter, index);
}