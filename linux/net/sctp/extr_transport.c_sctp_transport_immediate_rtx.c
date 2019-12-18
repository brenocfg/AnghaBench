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
struct sctp_transport {scalar_t__ rto; int /*<<< orphan*/  T3_rtx_timer; TYPE_1__* asoc; } ;
struct TYPE_2__ {int /*<<< orphan*/  outqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_RTXR_T3_RTX ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sctp_retransmit (int /*<<< orphan*/ *,struct sctp_transport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_transport_hold (struct sctp_transport*) ; 
 int /*<<< orphan*/  sctp_transport_put (struct sctp_transport*) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

void sctp_transport_immediate_rtx(struct sctp_transport *t)
{
	/* Stop pending T3_rtx_timer */
	if (del_timer(&t->T3_rtx_timer))
		sctp_transport_put(t);

	sctp_retransmit(&t->asoc->outqueue, t, SCTP_RTXR_T3_RTX);
	if (!timer_pending(&t->T3_rtx_timer)) {
		if (!mod_timer(&t->T3_rtx_timer, jiffies + t->rto))
			sctp_transport_hold(t);
	}
}