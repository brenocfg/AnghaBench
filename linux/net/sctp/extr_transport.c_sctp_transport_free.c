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
struct sctp_transport {int /*<<< orphan*/  asoc; int /*<<< orphan*/  proto_unreach_timer; int /*<<< orphan*/  reconf_timer; int /*<<< orphan*/  T3_rtx_timer; int /*<<< orphan*/  hb_timer; } ;

/* Variables and functions */
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_association_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_transport_put (struct sctp_transport*) ; 

void sctp_transport_free(struct sctp_transport *transport)
{
	/* Try to delete the heartbeat timer.  */
	if (del_timer(&transport->hb_timer))
		sctp_transport_put(transport);

	/* Delete the T3_rtx timer if it's active.
	 * There is no point in not doing this now and letting
	 * structure hang around in memory since we know
	 * the tranport is going away.
	 */
	if (del_timer(&transport->T3_rtx_timer))
		sctp_transport_put(transport);

	if (del_timer(&transport->reconf_timer))
		sctp_transport_put(transport);

	/* Delete the ICMP proto unreachable timer if it's active. */
	if (del_timer(&transport->proto_unreach_timer))
		sctp_association_put(transport->asoc);

	sctp_transport_put(transport);
}