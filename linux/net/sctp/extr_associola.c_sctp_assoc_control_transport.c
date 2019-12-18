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
struct sockaddr_storage {int dummy; } ;
struct sctp_ulpevent {int dummy; } ;
struct sctp_transport {TYPE_1__* af_specific; int /*<<< orphan*/  ipaddr; int /*<<< orphan*/  state; int /*<<< orphan*/  cwnd; } ;
struct TYPE_6__ {TYPE_2__* si; } ;
struct sctp_association {int /*<<< orphan*/  ulpq; TYPE_3__ stream; int /*<<< orphan*/  pathmtu; } ;
typedef  int /*<<< orphan*/  sctp_sn_error_t ;
typedef  enum sctp_transport_cmd { ____Placeholder_sctp_transport_cmd } sctp_transport_cmd ;
struct TYPE_5__ {int /*<<< orphan*/  (* enqueue_event ) (int /*<<< orphan*/ *,struct sctp_ulpevent*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  sockaddr_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_ACTIVE ; 
 int SCTP_ADDR_AVAILABLE ; 
 int SCTP_ADDR_CONFIRMED ; 
 int SCTP_ADDR_UNREACHABLE ; 
 int /*<<< orphan*/  SCTP_HEARTBEAT_SUCCESS ; 
 int /*<<< orphan*/  SCTP_INACTIVE ; 
 int /*<<< orphan*/  SCTP_PF ; 
#define  SCTP_TRANSPORT_DOWN 130 
#define  SCTP_TRANSPORT_PF 129 
#define  SCTP_TRANSPORT_UP 128 
 int /*<<< orphan*/  SCTP_UNCONFIRMED ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_storage*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sctp_select_active_and_retran_path (struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_transport_dst_release (struct sctp_transport*) ; 
 struct sctp_ulpevent* sctp_ulpevent_make_peer_addr_change (struct sctp_association*,struct sockaddr_storage*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct sctp_ulpevent*) ; 

void sctp_assoc_control_transport(struct sctp_association *asoc,
				  struct sctp_transport *transport,
				  enum sctp_transport_cmd command,
				  sctp_sn_error_t error)
{
	struct sctp_ulpevent *event;
	struct sockaddr_storage addr;
	int spc_state = 0;
	bool ulp_notify = true;

	/* Record the transition on the transport.  */
	switch (command) {
	case SCTP_TRANSPORT_UP:
		/* If we are moving from UNCONFIRMED state due
		 * to heartbeat success, report the SCTP_ADDR_CONFIRMED
		 * state to the user, otherwise report SCTP_ADDR_AVAILABLE.
		 */
		if (SCTP_UNCONFIRMED == transport->state &&
		    SCTP_HEARTBEAT_SUCCESS == error)
			spc_state = SCTP_ADDR_CONFIRMED;
		else
			spc_state = SCTP_ADDR_AVAILABLE;
		/* Don't inform ULP about transition from PF to
		 * active state and set cwnd to 1 MTU, see SCTP
		 * Quick failover draft section 5.1, point 5
		 */
		if (transport->state == SCTP_PF) {
			ulp_notify = false;
			transport->cwnd = asoc->pathmtu;
		}
		transport->state = SCTP_ACTIVE;
		break;

	case SCTP_TRANSPORT_DOWN:
		/* If the transport was never confirmed, do not transition it
		 * to inactive state.  Also, release the cached route since
		 * there may be a better route next time.
		 */
		if (transport->state != SCTP_UNCONFIRMED)
			transport->state = SCTP_INACTIVE;
		else {
			sctp_transport_dst_release(transport);
			ulp_notify = false;
		}

		spc_state = SCTP_ADDR_UNREACHABLE;
		break;

	case SCTP_TRANSPORT_PF:
		transport->state = SCTP_PF;
		ulp_notify = false;
		break;

	default:
		return;
	}

	/* Generate and send a SCTP_PEER_ADDR_CHANGE notification
	 * to the user.
	 */
	if (ulp_notify) {
		memset(&addr, 0, sizeof(struct sockaddr_storage));
		memcpy(&addr, &transport->ipaddr,
		       transport->af_specific->sockaddr_len);

		event = sctp_ulpevent_make_peer_addr_change(asoc, &addr,
					0, spc_state, error, GFP_ATOMIC);
		if (event)
			asoc->stream.si->enqueue_event(&asoc->ulpq, event);
	}

	/* Select new active and retran paths. */
	sctp_select_active_and_retran_path(asoc);
}