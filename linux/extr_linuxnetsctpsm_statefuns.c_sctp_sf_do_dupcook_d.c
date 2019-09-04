#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sctp_ulpevent {int dummy; } ;
struct sctp_endpoint {int dummy; } ;
struct sctp_cmd_seq {int dummy; } ;
struct sctp_chunk {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  auth_capable; scalar_t__ adaptation_ind; } ;
struct TYPE_3__ {int /*<<< orphan*/  sinit_max_instreams; int /*<<< orphan*/  sinit_num_ostreams; } ;
struct sctp_association {scalar_t__ state; TYPE_2__ peer; TYPE_1__ c; } ;
struct net {int dummy; } ;
typedef  enum sctp_disposition { ____Placeholder_sctp_disposition } sctp_disposition ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_AUTH_NO_AUTH ; 
 int /*<<< orphan*/  SCTP_CHUNK (struct sctp_chunk*) ; 
 int /*<<< orphan*/  SCTP_CMD_EVENT_ULP ; 
 int /*<<< orphan*/  SCTP_CMD_HB_TIMERS_START ; 
 int /*<<< orphan*/  SCTP_CMD_NEW_STATE ; 
 int /*<<< orphan*/  SCTP_CMD_REPLY ; 
 int /*<<< orphan*/  SCTP_CMD_TIMER_STOP ; 
 int /*<<< orphan*/  SCTP_COMM_UP ; 
 int SCTP_DISPOSITION_CONSUME ; 
 int SCTP_DISPOSITION_DISCARD ; 
 int SCTP_DISPOSITION_NOMEM ; 
 int /*<<< orphan*/  SCTP_EVENT_TIMEOUT_T1_COOKIE ; 
 int /*<<< orphan*/  SCTP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_MIB_CURRESTAB ; 
 int /*<<< orphan*/  SCTP_NULL () ; 
 int /*<<< orphan*/  SCTP_STATE (scalar_t__) ; 
 scalar_t__ SCTP_STATE_ESTABLISHED ; 
 int /*<<< orphan*/  SCTP_TO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_ULPEVENT (struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (struct sctp_cmd_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_auth_chunk_verify (struct net*,struct sctp_chunk*,struct sctp_association const*) ; 
 struct sctp_chunk* sctp_make_cookie_ack (struct sctp_association const*,struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_ulpevent_free (struct sctp_ulpevent*) ; 
 struct sctp_ulpevent* sctp_ulpevent_make_adaptation_indication (struct sctp_association const*,int /*<<< orphan*/ ) ; 
 struct sctp_ulpevent* sctp_ulpevent_make_assoc_change (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sctp_ulpevent* sctp_ulpevent_make_authkey (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum sctp_disposition sctp_sf_do_dupcook_d(
					struct net *net,
					const struct sctp_endpoint *ep,
					const struct sctp_association *asoc,
					struct sctp_chunk *chunk,
					struct sctp_cmd_seq *commands,
					struct sctp_association *new_asoc)
{
	struct sctp_ulpevent *ev = NULL, *ai_ev = NULL, *auth_ev = NULL;
	struct sctp_chunk *repl;

	/* Clarification from Implementor's Guide:
	 * D) When both local and remote tags match the endpoint should
	 * enter the ESTABLISHED state, if it is in the COOKIE-ECHOED state.
	 * It should stop any cookie timer that may be running and send
	 * a COOKIE ACK.
	 */

	if (!sctp_auth_chunk_verify(net, chunk, asoc))
		return SCTP_DISPOSITION_DISCARD;

	/* Don't accidentally move back into established state. */
	if (asoc->state < SCTP_STATE_ESTABLISHED) {
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
				SCTP_TO(SCTP_EVENT_TIMEOUT_T1_COOKIE));
		sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
				SCTP_STATE(SCTP_STATE_ESTABLISHED));
		SCTP_INC_STATS(net, SCTP_MIB_CURRESTAB);
		sctp_add_cmd_sf(commands, SCTP_CMD_HB_TIMERS_START,
				SCTP_NULL());

		/* RFC 2960 5.1 Normal Establishment of an Association
		 *
		 * D) IMPLEMENTATION NOTE: An implementation may choose
		 * to send the Communication Up notification to the
		 * SCTP user upon reception of a valid COOKIE
		 * ECHO chunk.
		 */
		ev = sctp_ulpevent_make_assoc_change(asoc, 0,
					     SCTP_COMM_UP, 0,
					     asoc->c.sinit_num_ostreams,
					     asoc->c.sinit_max_instreams,
					     NULL, GFP_ATOMIC);
		if (!ev)
			goto nomem;

		/* Sockets API Draft Section 5.3.1.6
		 * When a peer sends a Adaptation Layer Indication parameter,
		 * SCTP delivers this notification to inform the application
		 * that of the peers requested adaptation layer.
		 */
		if (asoc->peer.adaptation_ind) {
			ai_ev = sctp_ulpevent_make_adaptation_indication(asoc,
								 GFP_ATOMIC);
			if (!ai_ev)
				goto nomem;

		}

		if (!asoc->peer.auth_capable) {
			auth_ev = sctp_ulpevent_make_authkey(asoc, 0,
							     SCTP_AUTH_NO_AUTH,
							     GFP_ATOMIC);
			if (!auth_ev)
				goto nomem;
		}
	}

	repl = sctp_make_cookie_ack(asoc, chunk);
	if (!repl)
		goto nomem;

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(repl));

	if (ev)
		sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP,
				SCTP_ULPEVENT(ev));
	if (ai_ev)
		sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP,
					SCTP_ULPEVENT(ai_ev));
	if (auth_ev)
		sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP,
				SCTP_ULPEVENT(auth_ev));

	return SCTP_DISPOSITION_CONSUME;

nomem:
	if (auth_ev)
		sctp_ulpevent_free(auth_ev);
	if (ai_ev)
		sctp_ulpevent_free(ai_ev);
	if (ev)
		sctp_ulpevent_free(ev);
	return SCTP_DISPOSITION_NOMEM;
}