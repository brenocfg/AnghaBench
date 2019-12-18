#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union sctp_params {struct sctp_strreset_tsnreq* v; } ;
struct sctp_ulpevent {int dummy; } ;
struct sctp_strreset_tsnreq {int /*<<< orphan*/  request_seq; } ;
struct sctp_stream {size_t outcnt; size_t incnt; TYPE_1__* si; } ;
struct sctp_chunk {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  tsn_map; } ;
struct sctp_association {scalar_t__ strreset_inseq; scalar_t__* strreset_result; scalar_t__ ctsn_ack_point; int strreset_enable; scalar_t__ next_tsn; scalar_t__ adv_peer_ack_point; int /*<<< orphan*/  outqueue; TYPE_2__ peer; int /*<<< orphan*/  ulpq; struct sctp_stream stream; scalar_t__ strreset_outstanding; } ;
typedef  scalar_t__ __u32 ;
typedef  size_t __u16 ;
struct TYPE_8__ {scalar_t__ mid; } ;
struct TYPE_7__ {scalar_t__ mid_uo; scalar_t__ mid; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* report_ftsn ) (int /*<<< orphan*/ *,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int SCTP_ENABLE_RESET_ASSOC_REQ ; 
 TYPE_4__* SCTP_SI (struct sctp_stream*,size_t) ; 
 TYPE_3__* SCTP_SO (struct sctp_stream*,size_t) ; 
 scalar_t__ SCTP_STRRESET_DENIED ; 
 scalar_t__ SCTP_STRRESET_ERR_BAD_SEQNO ; 
 scalar_t__ SCTP_STRRESET_ERR_IN_PROGRESS ; 
 scalar_t__ SCTP_STRRESET_IN_PROGRESS ; 
 scalar_t__ SCTP_STRRESET_PERFORMED ; 
 int /*<<< orphan*/  SCTP_TSN_MAP_INITIAL ; 
 scalar_t__ TSN_lt (scalar_t__,scalar_t__) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 struct sctp_chunk* sctp_make_strreset_tsnresp (struct sctp_association*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sctp_outq_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_outq_is_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_tsnmap_get_ctsn (int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_tsnmap_get_max_tsn_seen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_tsnmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 struct sctp_ulpevent* sctp_ulpevent_make_assoc_reset_event (struct sctp_association*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_update_strreset_result (struct sctp_association*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,scalar_t__) ; 

struct sctp_chunk *sctp_process_strreset_tsnreq(
				struct sctp_association *asoc,
				union sctp_params param,
				struct sctp_ulpevent **evp)
{
	__u32 init_tsn = 0, next_tsn = 0, max_tsn_seen;
	struct sctp_strreset_tsnreq *tsnreq = param.v;
	struct sctp_stream *stream = &asoc->stream;
	__u32 result = SCTP_STRRESET_DENIED;
	__u32 request_seq;
	__u16 i;

	request_seq = ntohl(tsnreq->request_seq);
	if (TSN_lt(asoc->strreset_inseq, request_seq) ||
	    TSN_lt(request_seq, asoc->strreset_inseq - 2)) {
		result = SCTP_STRRESET_ERR_BAD_SEQNO;
		goto err;
	} else if (TSN_lt(request_seq, asoc->strreset_inseq)) {
		i = asoc->strreset_inseq - request_seq - 1;
		result = asoc->strreset_result[i];
		if (result == SCTP_STRRESET_PERFORMED) {
			next_tsn = asoc->ctsn_ack_point + 1;
			init_tsn =
				sctp_tsnmap_get_ctsn(&asoc->peer.tsn_map) + 1;
		}
		goto err;
	}

	if (!sctp_outq_is_empty(&asoc->outqueue)) {
		result = SCTP_STRRESET_IN_PROGRESS;
		goto err;
	}

	asoc->strreset_inseq++;

	if (!(asoc->strreset_enable & SCTP_ENABLE_RESET_ASSOC_REQ))
		goto out;

	if (asoc->strreset_outstanding) {
		result = SCTP_STRRESET_ERR_IN_PROGRESS;
		goto out;
	}

	/* G4: The same processing as though a FWD-TSN chunk (as defined in
	 *     [RFC3758]) with all streams affected and a new cumulative TSN
	 *     ACK of the Receiver's Next TSN minus 1 were received MUST be
	 *     performed.
	 */
	max_tsn_seen = sctp_tsnmap_get_max_tsn_seen(&asoc->peer.tsn_map);
	asoc->stream.si->report_ftsn(&asoc->ulpq, max_tsn_seen);

	/* G1: Compute an appropriate value for the Receiver's Next TSN -- the
	 *     TSN that the peer should use to send the next DATA chunk.  The
	 *     value SHOULD be the smallest TSN not acknowledged by the
	 *     receiver of the request plus 2^31.
	 */
	init_tsn = sctp_tsnmap_get_ctsn(&asoc->peer.tsn_map) + (1 << 31);
	sctp_tsnmap_init(&asoc->peer.tsn_map, SCTP_TSN_MAP_INITIAL,
			 init_tsn, GFP_ATOMIC);

	/* G3: The same processing as though a SACK chunk with no gap report
	 *     and a cumulative TSN ACK of the Sender's Next TSN minus 1 were
	 *     received MUST be performed.
	 */
	sctp_outq_free(&asoc->outqueue);

	/* G2: Compute an appropriate value for the local endpoint's next TSN,
	 *     i.e., the next TSN assigned by the receiver of the SSN/TSN reset
	 *     chunk.  The value SHOULD be the highest TSN sent by the receiver
	 *     of the request plus 1.
	 */
	next_tsn = asoc->next_tsn;
	asoc->ctsn_ack_point = next_tsn - 1;
	asoc->adv_peer_ack_point = asoc->ctsn_ack_point;

	/* G5:  The next expected and outgoing SSNs MUST be reset to 0 for all
	 *      incoming and outgoing streams.
	 */
	for (i = 0; i < stream->outcnt; i++) {
		SCTP_SO(stream, i)->mid = 0;
		SCTP_SO(stream, i)->mid_uo = 0;
	}
	for (i = 0; i < stream->incnt; i++)
		SCTP_SI(stream, i)->mid = 0;

	result = SCTP_STRRESET_PERFORMED;

	*evp = sctp_ulpevent_make_assoc_reset_event(asoc, 0, init_tsn,
						    next_tsn, GFP_ATOMIC);

out:
	sctp_update_strreset_result(asoc, result);
err:
	return sctp_make_strreset_tsnresp(asoc, result, request_seq,
					  next_tsn, init_tsn);
}