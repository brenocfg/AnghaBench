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
struct sctp_stream_priorities {int dummy; } ;
struct sctp_stream_out_ext {int /*<<< orphan*/  outq; struct sctp_stream_priorities* prio_head; } ;
struct sctp_outq {TYPE_1__* asoc; } ;
struct sctp_chunk {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_4__ {struct sctp_stream_out_ext* ext; } ;
struct TYPE_3__ {int /*<<< orphan*/  stream; } ;

/* Variables and functions */
 TYPE_2__* SCTP_SO (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_chunk_stream_no (struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_sched_prio_next_stream (struct sctp_stream_priorities*) ; 
 int /*<<< orphan*/  sctp_sched_prio_unsched (struct sctp_stream_out_ext*) ; 

__attribute__((used)) static void sctp_sched_prio_dequeue_done(struct sctp_outq *q,
					 struct sctp_chunk *ch)
{
	struct sctp_stream_priorities *prio;
	struct sctp_stream_out_ext *soute;
	__u16 sid;

	/* Last chunk on that msg, move to the next stream on
	 * this priority.
	 */
	sid = sctp_chunk_stream_no(ch);
	soute = SCTP_SO(&q->asoc->stream, sid)->ext;
	prio = soute->prio_head;

	sctp_sched_prio_next_stream(prio);

	if (list_empty(&soute->outq))
		sctp_sched_prio_unsched(soute);
}