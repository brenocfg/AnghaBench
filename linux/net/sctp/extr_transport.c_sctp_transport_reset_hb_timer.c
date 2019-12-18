#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  expires; } ;
struct sctp_transport {int /*<<< orphan*/  rto; TYPE_1__ hb_timer; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,scalar_t__) ; 
 scalar_t__ prandom_u32_max (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_transport_hold (struct sctp_transport*) ; 
 unsigned long sctp_transport_timeout (struct sctp_transport*) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  timer_pending (TYPE_1__*) ; 

void sctp_transport_reset_hb_timer(struct sctp_transport *transport)
{
	unsigned long expires;

	/* When a data chunk is sent, reset the heartbeat interval.  */
	expires = jiffies + sctp_transport_timeout(transport);
	if ((time_before(transport->hb_timer.expires, expires) ||
	     !timer_pending(&transport->hb_timer)) &&
	    !mod_timer(&transport->hb_timer,
		       expires + prandom_u32_max(transport->rto)))
		sctp_transport_hold(transport);
}