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
struct sctp_stream {int dummy; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_6__ {TYPE_2__* ext; } ;
struct TYPE_5__ {TYPE_1__* prio_head; } ;
struct TYPE_4__ {int /*<<< orphan*/  prio; } ;

/* Variables and functions */
 TYPE_3__* SCTP_SO (struct sctp_stream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sctp_sched_prio_get(struct sctp_stream *stream, __u16 sid,
			       __u16 *value)
{
	*value = SCTP_SO(stream, sid)->ext->prio_head->prio;
	return 0;
}