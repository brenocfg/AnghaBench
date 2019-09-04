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
typedef  union sctp_addr {int dummy; } sctp_addr ;
struct TYPE_6__ {int changeover_active; int cycling_changeover; int /*<<< orphan*/  next_tsn_at_change; } ;
struct sctp_transport {scalar_t__ state; TYPE_3__ cacc; int /*<<< orphan*/  ipaddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  out_qlen; int /*<<< orphan*/  outstanding_bytes; } ;
struct TYPE_4__ {struct sctp_transport* active_path; int /*<<< orphan*/  primary_addr; struct sctp_transport* primary_path; } ;
struct sctp_association {int /*<<< orphan*/  next_tsn; TYPE_2__ outqueue; TYPE_1__ peer; } ;

/* Variables and functions */
 scalar_t__ SCTP_ACTIVE ; 
 scalar_t__ SCTP_UNKNOWN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void sctp_assoc_set_primary(struct sctp_association *asoc,
			    struct sctp_transport *transport)
{
	int changeover = 0;

	/* it's a changeover only if we already have a primary path
	 * that we are changing
	 */
	if (asoc->peer.primary_path != NULL &&
	    asoc->peer.primary_path != transport)
		changeover = 1 ;

	asoc->peer.primary_path = transport;

	/* Set a default msg_name for events. */
	memcpy(&asoc->peer.primary_addr, &transport->ipaddr,
	       sizeof(union sctp_addr));

	/* If the primary path is changing, assume that the
	 * user wants to use this new path.
	 */
	if ((transport->state == SCTP_ACTIVE) ||
	    (transport->state == SCTP_UNKNOWN))
		asoc->peer.active_path = transport;

	/*
	 * SFR-CACC algorithm:
	 * Upon the receipt of a request to change the primary
	 * destination address, on the data structure for the new
	 * primary destination, the sender MUST do the following:
	 *
	 * 1) If CHANGEOVER_ACTIVE is set, then there was a switch
	 * to this destination address earlier. The sender MUST set
	 * CYCLING_CHANGEOVER to indicate that this switch is a
	 * double switch to the same destination address.
	 *
	 * Really, only bother is we have data queued or outstanding on
	 * the association.
	 */
	if (!asoc->outqueue.outstanding_bytes && !asoc->outqueue.out_qlen)
		return;

	if (transport->cacc.changeover_active)
		transport->cacc.cycling_changeover = changeover;

	/* 2) The sender MUST set CHANGEOVER_ACTIVE to indicate that
	 * a changeover has occurred.
	 */
	transport->cacc.changeover_active = changeover;

	/* 3) The sender MUST store the next TSN to be sent in
	 * next_tsn_at_change.
	 */
	transport->cacc.next_tsn_at_change = asoc->next_tsn;
}