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
union sctp_params {TYPE_2__* p; struct sctp_strreset_outreq* v; } ;
struct sctp_ulpevent {int dummy; } ;
struct sctp_transport {int /*<<< orphan*/  reconf_timer; } ;
struct sctp_strreset_outreq {int /*<<< orphan*/  response_seq; int /*<<< orphan*/ * list_of_streams; int /*<<< orphan*/  send_reset_at_tsn; int /*<<< orphan*/  request_seq; } ;
struct sctp_stream {size_t incnt; } ;
struct sctp_chunk {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tsn_map; } ;
struct sctp_association {size_t strreset_inseq; size_t* strreset_result; int strreset_enable; TYPE_3__* strreset_chunk; int /*<<< orphan*/  strreset_outstanding; int /*<<< orphan*/  strreset_outseq; TYPE_1__ peer; struct sctp_stream stream; } ;
typedef  size_t __u32 ;
typedef  size_t __u16 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_8__ {scalar_t__ mid; } ;
struct TYPE_7__ {struct sctp_transport* transport; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int SCTP_ENABLE_RESET_STREAM_REQ ; 
 int /*<<< orphan*/  SCTP_PARAM_RESET_IN_REQUEST ; 
 TYPE_4__* SCTP_SI (struct sctp_stream*,size_t) ; 
 int /*<<< orphan*/  SCTP_STREAM_RESET_INCOMING_SSN ; 
 size_t SCTP_STRRESET_DENIED ; 
 size_t SCTP_STRRESET_ERR_BAD_SEQNO ; 
 size_t SCTP_STRRESET_ERR_IN_PROGRESS ; 
 size_t SCTP_STRRESET_ERR_WRONG_SSN ; 
 size_t SCTP_STRRESET_IN_PROGRESS ; 
 size_t SCTP_STRRESET_PERFORMED ; 
 scalar_t__ TSN_lt (size_t,size_t) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 size_t ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_chunk_lookup_strreset_param (struct sctp_association*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_chunk_put (TYPE_3__*) ; 
 struct sctp_chunk* sctp_make_strreset_resp (struct sctp_association*,size_t,size_t) ; 
 int /*<<< orphan*/  sctp_transport_put (struct sctp_transport*) ; 
 scalar_t__ sctp_tsnmap_get_ctsn (int /*<<< orphan*/ *) ; 
 struct sctp_ulpevent* sctp_ulpevent_make_stream_reset_event (struct sctp_association*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_update_strreset_result (struct sctp_association*,size_t) ; 

struct sctp_chunk *sctp_process_strreset_outreq(
				struct sctp_association *asoc,
				union sctp_params param,
				struct sctp_ulpevent **evp)
{
	struct sctp_strreset_outreq *outreq = param.v;
	struct sctp_stream *stream = &asoc->stream;
	__u32 result = SCTP_STRRESET_DENIED;
	__be16 *str_p = NULL;
	__u32 request_seq;
	__u16 i, nums;

	request_seq = ntohl(outreq->request_seq);

	if (ntohl(outreq->send_reset_at_tsn) >
	    sctp_tsnmap_get_ctsn(&asoc->peer.tsn_map)) {
		result = SCTP_STRRESET_IN_PROGRESS;
		goto err;
	}

	if (TSN_lt(asoc->strreset_inseq, request_seq) ||
	    TSN_lt(request_seq, asoc->strreset_inseq - 2)) {
		result = SCTP_STRRESET_ERR_BAD_SEQNO;
		goto err;
	} else if (TSN_lt(request_seq, asoc->strreset_inseq)) {
		i = asoc->strreset_inseq - request_seq - 1;
		result = asoc->strreset_result[i];
		goto err;
	}
	asoc->strreset_inseq++;

	/* Check strreset_enable after inseq inc, as sender cannot tell
	 * the peer doesn't enable strreset after receiving response with
	 * result denied, as well as to keep consistent with bsd.
	 */
	if (!(asoc->strreset_enable & SCTP_ENABLE_RESET_STREAM_REQ))
		goto out;

	nums = (ntohs(param.p->length) - sizeof(*outreq)) / sizeof(__u16);
	str_p = outreq->list_of_streams;
	for (i = 0; i < nums; i++) {
		if (ntohs(str_p[i]) >= stream->incnt) {
			result = SCTP_STRRESET_ERR_WRONG_SSN;
			goto out;
		}
	}

	if (asoc->strreset_chunk) {
		if (!sctp_chunk_lookup_strreset_param(
				asoc, outreq->response_seq,
				SCTP_PARAM_RESET_IN_REQUEST)) {
			/* same process with outstanding isn't 0 */
			result = SCTP_STRRESET_ERR_IN_PROGRESS;
			goto out;
		}

		asoc->strreset_outstanding--;
		asoc->strreset_outseq++;

		if (!asoc->strreset_outstanding) {
			struct sctp_transport *t;

			t = asoc->strreset_chunk->transport;
			if (del_timer(&t->reconf_timer))
				sctp_transport_put(t);

			sctp_chunk_put(asoc->strreset_chunk);
			asoc->strreset_chunk = NULL;
		}
	}

	if (nums)
		for (i = 0; i < nums; i++)
			SCTP_SI(stream, ntohs(str_p[i]))->mid = 0;
	else
		for (i = 0; i < stream->incnt; i++)
			SCTP_SI(stream, i)->mid = 0;

	result = SCTP_STRRESET_PERFORMED;

	*evp = sctp_ulpevent_make_stream_reset_event(asoc,
		SCTP_STREAM_RESET_INCOMING_SSN, nums, str_p, GFP_ATOMIC);

out:
	sctp_update_strreset_result(asoc, result);
err:
	return sctp_make_strreset_resp(asoc, result, request_seq);
}