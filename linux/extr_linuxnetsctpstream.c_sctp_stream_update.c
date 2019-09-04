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
struct sctp_stream {scalar_t__ incnt; int /*<<< orphan*/  outcnt; int /*<<< orphan*/ * in; int /*<<< orphan*/ * out; } ;
struct sctp_sched_ops {int /*<<< orphan*/  (* sched_all ) (struct sctp_stream*) ;int /*<<< orphan*/  (* unsched_all ) (struct sctp_stream*) ;} ;

/* Variables and functions */
 struct sctp_sched_ops* sctp_sched_ops_from_stream (struct sctp_stream*) ; 
 int /*<<< orphan*/  sctp_stream_free (struct sctp_stream*) ; 
 int /*<<< orphan*/  sctp_stream_outq_migrate (struct sctp_stream*,struct sctp_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sctp_stream*) ; 
 int /*<<< orphan*/  stub2 (struct sctp_stream*) ; 

void sctp_stream_update(struct sctp_stream *stream, struct sctp_stream *new)
{
	struct sctp_sched_ops *sched = sctp_sched_ops_from_stream(stream);

	sched->unsched_all(stream);
	sctp_stream_outq_migrate(stream, new, new->outcnt);
	sctp_stream_free(stream);

	stream->out = new->out;
	stream->in  = new->in;
	stream->outcnt = new->outcnt;
	stream->incnt  = new->incnt;

	sched->sched_all(stream);

	new->out = NULL;
	new->in  = NULL;
	new->outcnt = 0;
	new->incnt  = 0;
}