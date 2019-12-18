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
union sctp_params {TYPE_1__* p; struct sctp_strreset_inreq* v; } ;
struct sctp_ulpevent {int dummy; } ;
struct sctp_strreset_inreq {int /*<<< orphan*/ * list_of_streams; int /*<<< orphan*/  request_seq; } ;
struct sctp_stream {size_t outcnt; } ;
struct sctp_chunk {int dummy; } ;
struct sctp_association {scalar_t__ strreset_inseq; scalar_t__* strreset_result; int strreset_enable; int strreset_outstanding; struct sctp_chunk* strreset_chunk; struct sctp_stream stream; } ;
typedef  scalar_t__ __u32 ;
typedef  size_t __u16 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {void* state; } ;
struct TYPE_3__ {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int SCTP_ENABLE_RESET_STREAM_REQ ; 
 TYPE_2__* SCTP_SO (struct sctp_stream*,size_t) ; 
 void* SCTP_STREAM_CLOSED ; 
 scalar_t__ SCTP_STRRESET_DENIED ; 
 scalar_t__ SCTP_STRRESET_ERR_BAD_SEQNO ; 
 scalar_t__ SCTP_STRRESET_ERR_IN_PROGRESS ; 
 scalar_t__ SCTP_STRRESET_ERR_WRONG_SSN ; 
 scalar_t__ SCTP_STRRESET_IN_PROGRESS ; 
 scalar_t__ SCTP_STRRESET_PERFORMED ; 
 scalar_t__ TSN_lt (scalar_t__,scalar_t__) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 size_t ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_chunk_hold (struct sctp_chunk*) ; 
 struct sctp_chunk* sctp_make_strreset_req (struct sctp_association*,size_t,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct sctp_chunk* sctp_make_strreset_resp (struct sctp_association*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sctp_stream_outq_is_empty (struct sctp_stream*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_update_strreset_result (struct sctp_association*,scalar_t__) ; 

struct sctp_chunk *sctp_process_strreset_inreq(
				struct sctp_association *asoc,
				union sctp_params param,
				struct sctp_ulpevent **evp)
{
	struct sctp_strreset_inreq *inreq = param.v;
	struct sctp_stream *stream = &asoc->stream;
	__u32 result = SCTP_STRRESET_DENIED;
	struct sctp_chunk *chunk = NULL;
	__u32 request_seq;
	__u16 i, nums;
	__be16 *str_p;

	request_seq = ntohl(inreq->request_seq);
	if (TSN_lt(asoc->strreset_inseq, request_seq) ||
	    TSN_lt(request_seq, asoc->strreset_inseq - 2)) {
		result = SCTP_STRRESET_ERR_BAD_SEQNO;
		goto err;
	} else if (TSN_lt(request_seq, asoc->strreset_inseq)) {
		i = asoc->strreset_inseq - request_seq - 1;
		result = asoc->strreset_result[i];
		if (result == SCTP_STRRESET_PERFORMED)
			return NULL;
		goto err;
	}
	asoc->strreset_inseq++;

	if (!(asoc->strreset_enable & SCTP_ENABLE_RESET_STREAM_REQ))
		goto out;

	if (asoc->strreset_outstanding) {
		result = SCTP_STRRESET_ERR_IN_PROGRESS;
		goto out;
	}

	nums = (ntohs(param.p->length) - sizeof(*inreq)) / sizeof(__u16);
	str_p = inreq->list_of_streams;
	for (i = 0; i < nums; i++) {
		if (ntohs(str_p[i]) >= stream->outcnt) {
			result = SCTP_STRRESET_ERR_WRONG_SSN;
			goto out;
		}
	}

	if (!sctp_stream_outq_is_empty(stream, nums, str_p)) {
		result = SCTP_STRRESET_IN_PROGRESS;
		asoc->strreset_inseq--;
		goto err;
	}

	chunk = sctp_make_strreset_req(asoc, nums, str_p, 1, 0);
	if (!chunk)
		goto out;

	if (nums)
		for (i = 0; i < nums; i++)
			SCTP_SO(stream, ntohs(str_p[i]))->state =
					       SCTP_STREAM_CLOSED;
	else
		for (i = 0; i < stream->outcnt; i++)
			SCTP_SO(stream, i)->state = SCTP_STREAM_CLOSED;

	asoc->strreset_chunk = chunk;
	asoc->strreset_outstanding = 1;
	sctp_chunk_hold(asoc->strreset_chunk);

	result = SCTP_STRRESET_PERFORMED;

out:
	sctp_update_strreset_result(asoc, result);
err:
	if (!chunk)
		chunk =  sctp_make_strreset_resp(asoc, result, request_seq);

	return chunk;
}