#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sctp_outq {int /*<<< orphan*/  abandoned; int /*<<< orphan*/  sacked; int /*<<< orphan*/  retransmit; int /*<<< orphan*/  control_chunk_list; int /*<<< orphan*/  out_chunk_list; struct sctp_association* asoc; } ;
struct sctp_association {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCTP_SS_DEFAULT ; 
 int /*<<< orphan*/  memset (struct sctp_outq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sctp_sched_set_sched (struct sctp_association*,int /*<<< orphan*/ ) ; 

void sctp_outq_init(struct sctp_association *asoc, struct sctp_outq *q)
{
	memset(q, 0, sizeof(struct sctp_outq));

	q->asoc = asoc;
	INIT_LIST_HEAD(&q->out_chunk_list);
	INIT_LIST_HEAD(&q->control_chunk_list);
	INIT_LIST_HEAD(&q->retransmit);
	INIT_LIST_HEAD(&q->sacked);
	INIT_LIST_HEAD(&q->abandoned);
	sctp_sched_set_sched(asoc, SCTP_SS_DEFAULT);
}