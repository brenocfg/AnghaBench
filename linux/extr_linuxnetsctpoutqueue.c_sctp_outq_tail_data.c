#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sctp_stream_out_ext {int /*<<< orphan*/  outq; } ;
struct sctp_outq {TYPE_1__* asoc; int /*<<< orphan*/  out_qlen; int /*<<< orphan*/  out_chunk_list; } ;
struct sctp_chunk {int /*<<< orphan*/  stream_list; TYPE_2__* skb; int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_6__ {struct sctp_stream_out_ext* ext; } ;
struct TYPE_5__ {scalar_t__ len; } ;
struct TYPE_4__ {int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 TYPE_3__* SCTP_SO (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_chunk_stream_no (struct sctp_chunk*) ; 

__attribute__((used)) static inline void sctp_outq_tail_data(struct sctp_outq *q,
				       struct sctp_chunk *ch)
{
	struct sctp_stream_out_ext *oute;
	__u16 stream;

	list_add_tail(&ch->list, &q->out_chunk_list);
	q->out_qlen += ch->skb->len;

	stream = sctp_chunk_stream_no(ch);
	oute = SCTP_SO(&q->asoc->stream, stream)->ext;
	list_add_tail(&ch->stream_list, &oute->outq);
}