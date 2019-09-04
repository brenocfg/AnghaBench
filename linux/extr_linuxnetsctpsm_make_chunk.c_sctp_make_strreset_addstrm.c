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
struct sctp_strreset_addstrm {scalar_t__ reserved; void* request_seq; void* number_of_streams; TYPE_1__ param_hdr; } ;
struct sctp_chunk {int dummy; } ;
struct sctp_association {scalar_t__ strreset_outseq; } ;
typedef  int /*<<< orphan*/  addstrm ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_PARAM_RESET_ADD_IN_STREAMS ; 
 int /*<<< orphan*/  SCTP_PARAM_RESET_ADD_OUT_STREAMS ; 
 void* htonl (scalar_t__) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,struct sctp_strreset_addstrm*) ; 
 struct sctp_chunk* sctp_make_reconf (struct sctp_association const*,int) ; 

struct sctp_chunk *sctp_make_strreset_addstrm(
					const struct sctp_association *asoc,
					__u16 out, __u16 in)
{
	struct sctp_strreset_addstrm addstrm;
	__u16 size = sizeof(addstrm);
	struct sctp_chunk *retval;

	retval = sctp_make_reconf(asoc, (!!out + !!in) * size);
	if (!retval)
		return NULL;

	if (out) {
		addstrm.param_hdr.type = SCTP_PARAM_RESET_ADD_OUT_STREAMS;
		addstrm.param_hdr.length = htons(size);
		addstrm.number_of_streams = htons(out);
		addstrm.request_seq = htonl(asoc->strreset_outseq);
		addstrm.reserved = 0;

		sctp_addto_chunk(retval, size, &addstrm);
	}

	if (in) {
		addstrm.param_hdr.type = SCTP_PARAM_RESET_ADD_IN_STREAMS;
		addstrm.param_hdr.length = htons(size);
		addstrm.number_of_streams = htons(in);
		addstrm.request_seq = htonl(asoc->strreset_outseq + !!out);
		addstrm.reserved = 0;

		sctp_addto_chunk(retval, size, &addstrm);
	}

	return retval;
}