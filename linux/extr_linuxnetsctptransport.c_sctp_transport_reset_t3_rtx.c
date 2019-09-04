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
struct sctp_transport {scalar_t__ rto; int /*<<< orphan*/  T3_rtx_timer; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sctp_transport_hold (struct sctp_transport*) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

void sctp_transport_reset_t3_rtx(struct sctp_transport *transport)
{
	/* RFC 2960 6.3.2 Retransmission Timer Rules
	 *
	 * R1) Every time a DATA chunk is sent to any address(including a
	 * retransmission), if the T3-rtx timer of that address is not running
	 * start it running so that it will expire after the RTO of that
	 * address.
	 */

	if (!timer_pending(&transport->T3_rtx_timer))
		if (!mod_timer(&transport->T3_rtx_timer,
			       jiffies + transport->rto))
			sctp_transport_hold(transport);
}