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
struct sctp_stream {int outcnt; int /*<<< orphan*/  out; } ;
struct sctp_sched_ops {int /*<<< orphan*/  (* free ) (struct sctp_stream*) ;int /*<<< orphan*/  (* sched_all ) (struct sctp_stream*) ;int /*<<< orphan*/  (* unsched_all ) (struct sctp_stream*) ;} ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 TYPE_1__* SCTP_SO (struct sctp_stream*,int) ; 
 int /*<<< orphan*/  SCTP_STREAM_OPEN ; 
 int /*<<< orphan*/  __GFP_NOWARN ; 
 int /*<<< orphan*/  genradix_free (int /*<<< orphan*/ *) ; 
 struct sctp_sched_ops* sctp_sched_ops_from_stream (struct sctp_stream*) ; 
 int sctp_stream_alloc_in (struct sctp_stream*,int,int /*<<< orphan*/ ) ; 
 int sctp_stream_alloc_out (struct sctp_stream*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_stream_interleave_init (struct sctp_stream*) ; 
 int /*<<< orphan*/  sctp_stream_outq_migrate (struct sctp_stream*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct sctp_stream*) ; 
 int /*<<< orphan*/  stub2 (struct sctp_stream*) ; 
 int /*<<< orphan*/  stub3 (struct sctp_stream*) ; 

int sctp_stream_init(struct sctp_stream *stream, __u16 outcnt, __u16 incnt,
		     gfp_t gfp)
{
	struct sctp_sched_ops *sched = sctp_sched_ops_from_stream(stream);
	int i, ret = 0;

	gfp |= __GFP_NOWARN;

	/* Initial stream->out size may be very big, so free it and alloc
	 * a new one with new outcnt to save memory if needed.
	 */
	if (outcnt == stream->outcnt)
		goto in;

	/* Filter out chunks queued on streams that won't exist anymore */
	sched->unsched_all(stream);
	sctp_stream_outq_migrate(stream, NULL, outcnt);
	sched->sched_all(stream);

	ret = sctp_stream_alloc_out(stream, outcnt, gfp);
	if (ret)
		goto out;

	for (i = 0; i < stream->outcnt; i++)
		SCTP_SO(stream, i)->state = SCTP_STREAM_OPEN;

in:
	sctp_stream_interleave_init(stream);
	if (!incnt)
		goto out;

	ret = sctp_stream_alloc_in(stream, incnt, gfp);
	if (ret) {
		sched->free(stream);
		genradix_free(&stream->out);
		stream->outcnt = 0;
		goto out;
	}

out:
	return ret;
}