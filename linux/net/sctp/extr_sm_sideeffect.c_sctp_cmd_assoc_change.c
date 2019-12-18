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
typedef  int /*<<< orphan*/  u8 ;
struct sctp_ulpevent {int dummy; } ;
struct sctp_cmd_seq {int dummy; } ;
struct TYPE_6__ {TYPE_2__* si; } ;
struct TYPE_4__ {int /*<<< orphan*/  sinit_max_instreams; int /*<<< orphan*/  sinit_num_ostreams; } ;
struct sctp_association {int /*<<< orphan*/  ulpq; TYPE_3__ stream; TYPE_1__ c; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* enqueue_event ) (int /*<<< orphan*/ *,struct sctp_ulpevent*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sctp_ulpevent* sctp_ulpevent_make_assoc_change (struct sctp_association*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct sctp_ulpevent*) ; 

__attribute__((used)) static void sctp_cmd_assoc_change(struct sctp_cmd_seq *commands,
				  struct sctp_association *asoc,
				  u8 state)
{
	struct sctp_ulpevent *ev;

	ev = sctp_ulpevent_make_assoc_change(asoc, 0, state, 0,
					    asoc->c.sinit_num_ostreams,
					    asoc->c.sinit_max_instreams,
					    NULL, GFP_ATOMIC);
	if (ev)
		asoc->stream.si->enqueue_event(&asoc->ulpq, ev);
}