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
struct sctp_stream {int /*<<< orphan*/ * rr_next; int /*<<< orphan*/  rr_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sctp_sched_rr_init(struct sctp_stream *stream)
{
	INIT_LIST_HEAD(&stream->rr_list);
	stream->rr_next = NULL;

	return 0;
}