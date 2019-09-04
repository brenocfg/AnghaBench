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
typedef  int /*<<< orphan*/  tsnresp ;
struct TYPE_2__ {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct sctp_strreset_resptsn {void* receivers_next_tsn; void* senders_next_tsn; void* result; void* response_seq; TYPE_1__ param_hdr; } ;
struct sctp_chunk {int dummy; } ;
struct sctp_association {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_PARAM_RESET_RESPONSE ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,int,struct sctp_strreset_resptsn*) ; 
 struct sctp_chunk* sctp_make_reconf (struct sctp_association*,int) ; 

struct sctp_chunk *sctp_make_strreset_tsnresp(struct sctp_association *asoc,
					      __u32 result, __u32 sn,
					      __u32 sender_tsn,
					      __u32 receiver_tsn)
{
	struct sctp_strreset_resptsn tsnresp;
	__u16 length = sizeof(tsnresp);
	struct sctp_chunk *retval;

	retval = sctp_make_reconf(asoc, length);
	if (!retval)
		return NULL;

	tsnresp.param_hdr.type = SCTP_PARAM_RESET_RESPONSE;
	tsnresp.param_hdr.length = htons(length);

	tsnresp.response_seq = htonl(sn);
	tsnresp.result = htonl(result);
	tsnresp.senders_next_tsn = htonl(sender_tsn);
	tsnresp.receivers_next_tsn = htonl(receiver_tsn);

	sctp_addto_chunk(retval, sizeof(tsnresp), &tsnresp);

	return retval;
}