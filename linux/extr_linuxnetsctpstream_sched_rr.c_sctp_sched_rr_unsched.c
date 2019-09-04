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
struct sctp_stream_out_ext {int /*<<< orphan*/  rr_list; } ;
struct sctp_stream {struct sctp_stream_out_ext* rr_next; int /*<<< orphan*/  rr_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_sched_rr_next_stream (struct sctp_stream*) ; 

__attribute__((used)) static void sctp_sched_rr_unsched(struct sctp_stream *stream,
				  struct sctp_stream_out_ext *soute)
{
	if (stream->rr_next == soute)
		/* Try to move to the next stream */
		sctp_sched_rr_next_stream(stream);

	list_del_init(&soute->rr_list);

	/* If we have no other stream queued, clear next */
	if (list_empty(&stream->rr_list))
		stream->rr_next = NULL;
}