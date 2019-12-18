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
struct sctp_stream {int outcnt; int /*<<< orphan*/  in; int /*<<< orphan*/  out; } ;
struct sctp_sched_ops {int /*<<< orphan*/  (* free ) (struct sctp_stream*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  ext; } ;

/* Variables and functions */
 TYPE_1__* SCTP_SO (struct sctp_stream*,int) ; 
 int /*<<< orphan*/  genradix_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct sctp_sched_ops* sctp_sched_ops_from_stream (struct sctp_stream*) ; 
 int /*<<< orphan*/  stub1 (struct sctp_stream*) ; 

void sctp_stream_free(struct sctp_stream *stream)
{
	struct sctp_sched_ops *sched = sctp_sched_ops_from_stream(stream);
	int i;

	sched->free(stream);
	for (i = 0; i < stream->outcnt; i++)
		kfree(SCTP_SO(stream, i)->ext);
	genradix_free(&stream->out);
	genradix_free(&stream->in);
}