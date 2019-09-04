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
struct TYPE_2__ {void* length; int /*<<< orphan*/  type; } ;
struct sctp_strreset_outreq {void* request_seq; TYPE_1__ param_hdr; void* send_reset_at_tsn; void* response_seq; } ;
struct sctp_strreset_inreq {void* request_seq; TYPE_1__ param_hdr; void* send_reset_at_tsn; void* response_seq; } ;
struct sctp_chunk {int dummy; } ;
struct sctp_association {scalar_t__ strreset_outseq; scalar_t__ next_tsn; scalar_t__ strreset_inseq; } ;
typedef  int /*<<< orphan*/  outreq ;
typedef  int /*<<< orphan*/  inreq ;
typedef  int __u16 ;
typedef  struct sctp_strreset_outreq __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_PARAM_RESET_IN_REQUEST ; 
 int /*<<< orphan*/  SCTP_PARAM_RESET_OUT_REQUEST ; 
 void* htonl (scalar_t__) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,struct sctp_strreset_outreq*) ; 
 struct sctp_chunk* sctp_make_reconf (struct sctp_association const*,int) ; 

struct sctp_chunk *sctp_make_strreset_req(
					const struct sctp_association *asoc,
					__u16 stream_num, __be16 *stream_list,
					bool out, bool in)
{
	__u16 stream_len = stream_num * sizeof(__u16);
	struct sctp_strreset_outreq outreq;
	struct sctp_strreset_inreq inreq;
	struct sctp_chunk *retval;
	__u16 outlen, inlen;

	outlen = (sizeof(outreq) + stream_len) * out;
	inlen = (sizeof(inreq) + stream_len) * in;

	retval = sctp_make_reconf(asoc, outlen + inlen);
	if (!retval)
		return NULL;

	if (outlen) {
		outreq.param_hdr.type = SCTP_PARAM_RESET_OUT_REQUEST;
		outreq.param_hdr.length = htons(outlen);
		outreq.request_seq = htonl(asoc->strreset_outseq);
		outreq.response_seq = htonl(asoc->strreset_inseq - 1);
		outreq.send_reset_at_tsn = htonl(asoc->next_tsn - 1);

		sctp_addto_chunk(retval, sizeof(outreq), &outreq);

		if (stream_len)
			sctp_addto_chunk(retval, stream_len, stream_list);
	}

	if (inlen) {
		inreq.param_hdr.type = SCTP_PARAM_RESET_IN_REQUEST;
		inreq.param_hdr.length = htons(inlen);
		inreq.request_seq = htonl(asoc->strreset_outseq + out);

		sctp_addto_chunk(retval, sizeof(inreq), &inreq);

		if (stream_len)
			sctp_addto_chunk(retval, stream_len, stream_list);
	}

	return retval;
}