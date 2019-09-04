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
typedef  union sctp_subtype {int dummy; } sctp_subtype ;
typedef  union sctp_arg {int dummy; } sctp_arg ;
typedef  int /*<<< orphan*/  u8 ;
struct sctp_endpoint {int dummy; } ;
struct sctp_cmd_seq {int dummy; } ;
struct TYPE_3__ {scalar_t__ data_hdr; } ;
struct sctp_chunk {scalar_t__ end_of_packet; TYPE_2__* chunk_hdr; TYPE_1__ subh; } ;
struct sctp_association {scalar_t__* timeouts; int /*<<< orphan*/  stream; } ;
struct net {int dummy; } ;
typedef  enum sctp_disposition { ____Placeholder_sctp_disposition } sctp_disposition ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  SCTP_CMD_GEN_SACK ; 
 int /*<<< orphan*/  SCTP_CMD_REPORT_BAD_TAG ; 
 int /*<<< orphan*/  SCTP_CMD_TIMER_RESTART ; 
 int SCTP_DATA_SACK_IMM ; 
 int SCTP_DISPOSITION_ABORT ; 
 int SCTP_DISPOSITION_CONSUME ; 
 int SCTP_DISPOSITION_DISCARD ; 
 size_t SCTP_EVENT_TIMEOUT_AUTOCLOSE ; 
 union sctp_arg SCTP_FORCE () ; 
#define  SCTP_IERROR_BAD_STREAM 134 
#define  SCTP_IERROR_DUP_TSN 133 
#define  SCTP_IERROR_HIGH_TSN 132 
#define  SCTP_IERROR_IGNORE_TSN 131 
#define  SCTP_IERROR_NO_DATA 130 
#define  SCTP_IERROR_NO_ERROR 129 
#define  SCTP_IERROR_PROTO_VIOLATION 128 
 int /*<<< orphan*/  SCTP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_MIB_IN_DATA_CHUNK_DISCARDS ; 
 union sctp_arg SCTP_NOFORCE () ; 
 union sctp_arg SCTP_NULL () ; 
 union sctp_arg SCTP_TO (size_t) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (struct sctp_cmd_seq*,int /*<<< orphan*/ ,union sctp_arg) ; 
 int /*<<< orphan*/  sctp_chunk_length_valid (struct sctp_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_datachk_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_datahdr_len (int /*<<< orphan*/ *) ; 
 int sctp_eat_data (struct sctp_association const*,struct sctp_chunk*,struct sctp_cmd_seq*) ; 
 int sctp_sf_abort_violation (struct net*,struct sctp_endpoint const*,struct sctp_association const*,struct sctp_chunk*,struct sctp_cmd_seq*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sctp_sf_pdiscard (struct net*,struct sctp_endpoint const*,struct sctp_association const*,union sctp_subtype const,void*,struct sctp_cmd_seq*) ; 
 int sctp_sf_violation_chunklen (struct net*,struct sctp_endpoint const*,struct sctp_association const*,union sctp_subtype const,void*,struct sctp_cmd_seq*) ; 
 int /*<<< orphan*/  sctp_vtag_verify (struct sctp_chunk*,struct sctp_association const*) ; 

enum sctp_disposition sctp_sf_eat_data_6_2(struct net *net,
					   const struct sctp_endpoint *ep,
					   const struct sctp_association *asoc,
					   const union sctp_subtype type,
					   void *arg,
					   struct sctp_cmd_seq *commands)
{
	union sctp_arg force = SCTP_NOFORCE();
	struct sctp_chunk *chunk = arg;
	int error;

	if (!sctp_vtag_verify(chunk, asoc)) {
		sctp_add_cmd_sf(commands, SCTP_CMD_REPORT_BAD_TAG,
				SCTP_NULL());
		return sctp_sf_pdiscard(net, ep, asoc, type, arg, commands);
	}

	if (!sctp_chunk_length_valid(chunk, sctp_datachk_len(&asoc->stream)))
		return sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	error = sctp_eat_data(asoc, chunk, commands);
	switch (error) {
	case SCTP_IERROR_NO_ERROR:
		break;
	case SCTP_IERROR_HIGH_TSN:
	case SCTP_IERROR_BAD_STREAM:
		SCTP_INC_STATS(net, SCTP_MIB_IN_DATA_CHUNK_DISCARDS);
		goto discard_noforce;
	case SCTP_IERROR_DUP_TSN:
	case SCTP_IERROR_IGNORE_TSN:
		SCTP_INC_STATS(net, SCTP_MIB_IN_DATA_CHUNK_DISCARDS);
		goto discard_force;
	case SCTP_IERROR_NO_DATA:
		return SCTP_DISPOSITION_ABORT;
	case SCTP_IERROR_PROTO_VIOLATION:
		return sctp_sf_abort_violation(net, ep, asoc, chunk, commands,
					       (u8 *)chunk->subh.data_hdr,
					       sctp_datahdr_len(&asoc->stream));
	default:
		BUG();
	}

	if (chunk->chunk_hdr->flags & SCTP_DATA_SACK_IMM)
		force = SCTP_FORCE();

	if (asoc->timeouts[SCTP_EVENT_TIMEOUT_AUTOCLOSE]) {
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
				SCTP_TO(SCTP_EVENT_TIMEOUT_AUTOCLOSE));
	}

	/* If this is the last chunk in a packet, we need to count it
	 * toward sack generation.  Note that we need to SACK every
	 * OTHER packet containing data chunks, EVEN IF WE DISCARD
	 * THEM.  We elect to NOT generate SACK's if the chunk fails
	 * the verification tag test.
	 *
	 * RFC 2960 6.2 Acknowledgement on Reception of DATA Chunks
	 *
	 * The SCTP endpoint MUST always acknowledge the reception of
	 * each valid DATA chunk.
	 *
	 * The guidelines on delayed acknowledgement algorithm
	 * specified in  Section 4.2 of [RFC2581] SHOULD be followed.
	 * Specifically, an acknowledgement SHOULD be generated for at
	 * least every second packet (not every second DATA chunk)
	 * received, and SHOULD be generated within 200 ms of the
	 * arrival of any unacknowledged DATA chunk.  In some
	 * situations it may be beneficial for an SCTP transmitter to
	 * be more conservative than the algorithms detailed in this
	 * document allow. However, an SCTP transmitter MUST NOT be
	 * more aggressive than the following algorithms allow.
	 */
	if (chunk->end_of_packet)
		sctp_add_cmd_sf(commands, SCTP_CMD_GEN_SACK, force);

	return SCTP_DISPOSITION_CONSUME;

discard_force:
	/* RFC 2960 6.2 Acknowledgement on Reception of DATA Chunks
	 *
	 * When a packet arrives with duplicate DATA chunk(s) and with
	 * no new DATA chunk(s), the endpoint MUST immediately send a
	 * SACK with no delay.  If a packet arrives with duplicate
	 * DATA chunk(s) bundled with new DATA chunks, the endpoint
	 * MAY immediately send a SACK.  Normally receipt of duplicate
	 * DATA chunks will occur when the original SACK chunk was lost
	 * and the peer's RTO has expired.  The duplicate TSN number(s)
	 * SHOULD be reported in the SACK as duplicate.
	 */
	/* In our case, we split the MAY SACK advice up whether or not
	 * the last chunk is a duplicate.'
	 */
	if (chunk->end_of_packet)
		sctp_add_cmd_sf(commands, SCTP_CMD_GEN_SACK, SCTP_FORCE());
	return SCTP_DISPOSITION_DISCARD;

discard_noforce:
	if (chunk->end_of_packet)
		sctp_add_cmd_sf(commands, SCTP_CMD_GEN_SACK, force);

	return SCTP_DISPOSITION_DISCARD;
}