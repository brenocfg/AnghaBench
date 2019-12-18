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
struct sctp_stream_priorities {int dummy; } ;
struct sctp_stream_out_ext {struct sctp_stream_priorities* prio_head; } ;
struct sctp_stream_out {struct sctp_stream_out_ext* ext; } ;
struct sctp_stream {int outcnt; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int __u16 ;

/* Variables and functions */
 int ENOMEM ; 
 struct sctp_stream_out* SCTP_SO (struct sctp_stream*,int) ; 
 int /*<<< orphan*/  kfree (struct sctp_stream_priorities*) ; 
 struct sctp_stream_priorities* sctp_sched_prio_get_head (struct sctp_stream*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_sched_prio_sched (struct sctp_stream*,struct sctp_stream_out_ext*) ; 
 int sctp_sched_prio_unsched (struct sctp_stream_out_ext*) ; 

__attribute__((used)) static int sctp_sched_prio_set(struct sctp_stream *stream, __u16 sid,
			       __u16 prio, gfp_t gfp)
{
	struct sctp_stream_out *sout = SCTP_SO(stream, sid);
	struct sctp_stream_out_ext *soute = sout->ext;
	struct sctp_stream_priorities *prio_head, *old;
	bool reschedule = false;
	int i;

	prio_head = sctp_sched_prio_get_head(stream, prio, gfp);
	if (!prio_head)
		return -ENOMEM;

	reschedule = sctp_sched_prio_unsched(soute);
	old = soute->prio_head;
	soute->prio_head = prio_head;
	if (reschedule)
		sctp_sched_prio_sched(stream, soute);

	if (!old)
		/* Happens when we set the priority for the first time */
		return 0;

	for (i = 0; i < stream->outcnt; i++) {
		soute = SCTP_SO(stream, i)->ext;
		if (soute && soute->prio_head == old)
			/* It's still in use, nothing else to do here. */
			return 0;
	}

	/* No hits, we are good to free it. */
	kfree(old);

	return 0;
}