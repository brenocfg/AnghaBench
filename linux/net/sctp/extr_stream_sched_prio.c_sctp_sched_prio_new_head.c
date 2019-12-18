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
struct sctp_stream_priorities {int prio; int /*<<< orphan*/ * next; int /*<<< orphan*/  active; int /*<<< orphan*/  prio_sched; } ;
struct sctp_stream {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct sctp_stream_priorities* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sctp_stream_priorities *sctp_sched_prio_new_head(
			struct sctp_stream *stream, int prio, gfp_t gfp)
{
	struct sctp_stream_priorities *p;

	p = kmalloc(sizeof(*p), gfp);
	if (!p)
		return NULL;

	INIT_LIST_HEAD(&p->prio_sched);
	INIT_LIST_HEAD(&p->active);
	p->next = NULL;
	p->prio = prio;

	return p;
}