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
struct sctp_strreset_outreq {int dummy; } ;
struct sctp_strreset_inreq {int dummy; } ;
struct sctp_stream {int outcnt; int incnt; } ;
struct sctp_reset_streams {int srs_flags; int srs_number_streams; int* srs_stream_list; } ;
struct sctp_reconf_chunk {int dummy; } ;
struct sctp_chunk {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  reconf_capable; } ;
struct sctp_association {int strreset_enable; int strreset_outstanding; struct sctp_chunk* strreset_chunk; TYPE_1__ peer; struct sctp_stream stream; } ;
typedef  int __u16 ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_4__ {void* state; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SCTP_ENABLE_RESET_STREAM_REQ ; 
 int SCTP_MAX_CHUNK_LEN ; 
 TYPE_2__* SCTP_SO (struct sctp_stream*,int) ; 
 void* SCTP_STREAM_CLOSED ; 
 void* SCTP_STREAM_OPEN ; 
 int SCTP_STREAM_RESET_INCOMING ; 
 int SCTP_STREAM_RESET_OUTGOING ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_chunk_hold (struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_chunk_put (struct sctp_chunk*) ; 
 struct sctp_chunk* sctp_make_strreset_req (struct sctp_association*,int,int /*<<< orphan*/ *,int,int) ; 
 int sctp_send_reconf (struct sctp_association*,struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_stream_outq_is_empty (struct sctp_stream*,int,int /*<<< orphan*/ *) ; 

int sctp_send_reset_streams(struct sctp_association *asoc,
			    struct sctp_reset_streams *params)
{
	struct sctp_stream *stream = &asoc->stream;
	__u16 i, str_nums, *str_list;
	struct sctp_chunk *chunk;
	int retval = -EINVAL;
	__be16 *nstr_list;
	bool out, in;

	if (!asoc->peer.reconf_capable ||
	    !(asoc->strreset_enable & SCTP_ENABLE_RESET_STREAM_REQ)) {
		retval = -ENOPROTOOPT;
		goto out;
	}

	if (asoc->strreset_outstanding) {
		retval = -EINPROGRESS;
		goto out;
	}

	out = params->srs_flags & SCTP_STREAM_RESET_OUTGOING;
	in  = params->srs_flags & SCTP_STREAM_RESET_INCOMING;
	if (!out && !in)
		goto out;

	str_nums = params->srs_number_streams;
	str_list = params->srs_stream_list;
	if (str_nums) {
		int param_len = 0;

		if (out) {
			for (i = 0; i < str_nums; i++)
				if (str_list[i] >= stream->outcnt)
					goto out;

			param_len = str_nums * sizeof(__u16) +
				    sizeof(struct sctp_strreset_outreq);
		}

		if (in) {
			for (i = 0; i < str_nums; i++)
				if (str_list[i] >= stream->incnt)
					goto out;

			param_len += str_nums * sizeof(__u16) +
				     sizeof(struct sctp_strreset_inreq);
		}

		if (param_len > SCTP_MAX_CHUNK_LEN -
				sizeof(struct sctp_reconf_chunk))
			goto out;
	}

	nstr_list = kcalloc(str_nums, sizeof(__be16), GFP_KERNEL);
	if (!nstr_list) {
		retval = -ENOMEM;
		goto out;
	}

	for (i = 0; i < str_nums; i++)
		nstr_list[i] = htons(str_list[i]);

	if (out && !sctp_stream_outq_is_empty(stream, str_nums, nstr_list)) {
		kfree(nstr_list);
		retval = -EAGAIN;
		goto out;
	}

	chunk = sctp_make_strreset_req(asoc, str_nums, nstr_list, out, in);

	kfree(nstr_list);

	if (!chunk) {
		retval = -ENOMEM;
		goto out;
	}

	if (out) {
		if (str_nums)
			for (i = 0; i < str_nums; i++)
				SCTP_SO(stream, str_list[i])->state =
						       SCTP_STREAM_CLOSED;
		else
			for (i = 0; i < stream->outcnt; i++)
				SCTP_SO(stream, i)->state = SCTP_STREAM_CLOSED;
	}

	asoc->strreset_chunk = chunk;
	sctp_chunk_hold(asoc->strreset_chunk);

	retval = sctp_send_reconf(asoc, chunk);
	if (retval) {
		sctp_chunk_put(asoc->strreset_chunk);
		asoc->strreset_chunk = NULL;
		if (!out)
			goto out;

		if (str_nums)
			for (i = 0; i < str_nums; i++)
				SCTP_SO(stream, str_list[i])->state =
						       SCTP_STREAM_OPEN;
		else
			for (i = 0; i < stream->outcnt; i++)
				SCTP_SO(stream, i)->state = SCTP_STREAM_OPEN;

		goto out;
	}

	asoc->strreset_outstanding = out + in;

out:
	return retval;
}