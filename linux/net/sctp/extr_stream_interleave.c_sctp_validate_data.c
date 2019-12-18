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
struct sctp_stream {int dummy; } ;
struct TYPE_5__ {TYPE_4__* data_hdr; } ;
struct sctp_chunk {TYPE_1__ subh; TYPE_3__* asoc; TYPE_2__* chunk_hdr; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_8__ {int /*<<< orphan*/  ssn; } ;
struct TYPE_7__ {struct sctp_stream stream; } ;
struct TYPE_6__ {scalar_t__ type; int flags; } ;

/* Variables and functions */
 scalar_t__ SCTP_CID_DATA ; 
 int SCTP_DATA_UNORDERED ; 
 int /*<<< orphan*/  SSN_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_chunk_stream_no (struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_ssn_peek (struct sctp_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sctp_validate_data(struct sctp_chunk *chunk)
{
	struct sctp_stream *stream;
	__u16 sid, ssn;

	if (chunk->chunk_hdr->type != SCTP_CID_DATA)
		return false;

	if (chunk->chunk_hdr->flags & SCTP_DATA_UNORDERED)
		return true;

	stream = &chunk->asoc->stream;
	sid = sctp_chunk_stream_no(chunk);
	ssn = ntohs(chunk->subh.data_hdr->ssn);

	return !SSN_lt(ssn, sctp_ssn_peek(stream, in, sid));
}