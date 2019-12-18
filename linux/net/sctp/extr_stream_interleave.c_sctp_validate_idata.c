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
struct TYPE_5__ {TYPE_4__* idata_hdr; } ;
struct sctp_chunk {TYPE_1__ subh; TYPE_3__* asoc; TYPE_2__* chunk_hdr; } ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_8__ {int /*<<< orphan*/  mid; } ;
struct TYPE_7__ {struct sctp_stream stream; } ;
struct TYPE_6__ {scalar_t__ type; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MID_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SCTP_CID_I_DATA ; 
 int SCTP_DATA_UNORDERED ; 
 int /*<<< orphan*/  in ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_chunk_stream_no (struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_mid_peek (struct sctp_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool sctp_validate_idata(struct sctp_chunk *chunk)
{
	struct sctp_stream *stream;
	__u32 mid;
	__u16 sid;

	if (chunk->chunk_hdr->type != SCTP_CID_I_DATA)
		return false;

	if (chunk->chunk_hdr->flags & SCTP_DATA_UNORDERED)
		return true;

	stream = &chunk->asoc->stream;
	sid = sctp_chunk_stream_no(chunk);
	mid = ntohl(chunk->subh.idata_hdr->mid);

	return !MID_lt(mid, sctp_mid_peek(stream, in, sid));
}