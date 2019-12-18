#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sctp_ulpevent {int dummy; } ;
struct sctp_init_chunk {int dummy; } ;
struct sctp_endpoint {int dummy; } ;
struct sctp_cmd_seq {int dummy; } ;
struct TYPE_9__ {TYPE_2__* cookie_hdr; } ;
struct sctp_chunk {TYPE_4__* chunk_hdr; TYPE_3__ subh; } ;
struct TYPE_12__ {int /*<<< orphan*/  sk; } ;
struct TYPE_11__ {int /*<<< orphan*/  sinit_max_instreams; int /*<<< orphan*/  sinit_num_ostreams; } ;
struct sctp_association {TYPE_6__ base; TYPE_5__ c; } ;
struct net {int dummy; } ;
typedef  enum sctp_disposition { ____Placeholder_sctp_disposition } sctp_disposition ;
struct TYPE_10__ {int /*<<< orphan*/  type; } ;
struct TYPE_7__ {struct sctp_init_chunk* peer_init; } ;
struct TYPE_8__ {TYPE_1__ c; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSING ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_ASOC (struct sctp_association*) ; 
 int /*<<< orphan*/  SCTP_CHUNK (struct sctp_chunk*) ; 
 int /*<<< orphan*/  SCTP_CMD_EVENT_ULP ; 
 int /*<<< orphan*/  SCTP_CMD_NEW_STATE ; 
 int /*<<< orphan*/  SCTP_CMD_PURGE_ASCONF_QUEUE ; 
 int /*<<< orphan*/  SCTP_CMD_PURGE_OUTQUEUE ; 
 int /*<<< orphan*/  SCTP_CMD_REPLY ; 
 int /*<<< orphan*/  SCTP_CMD_T3_RTX_TIMERS_STOP ; 
 int /*<<< orphan*/  SCTP_CMD_TIMER_STOP ; 
 int /*<<< orphan*/  SCTP_CMD_UPDATE_ASSOC ; 
 int SCTP_DISPOSITION_CONSUME ; 
 int SCTP_DISPOSITION_DISCARD ; 
 int SCTP_DISPOSITION_NOMEM ; 
 int /*<<< orphan*/  SCTP_ERROR_COOKIE_IN_SHUTDOWN ; 
 int /*<<< orphan*/  SCTP_EVENT_TIMEOUT_SACK ; 
 int /*<<< orphan*/  SCTP_EVENT_TIMEOUT_T4_RTO ; 
 int /*<<< orphan*/  SCTP_NULL () ; 
 int /*<<< orphan*/  SCTP_RESTART ; 
 int /*<<< orphan*/  SCTP_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_STATE_ESTABLISHED ; 
 int /*<<< orphan*/  SCTP_ST_CHUNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_TO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_ULPEVENT (struct sctp_ulpevent*) ; 
 int /*<<< orphan*/  SHUTDOWN_ACK_SENT ; 
 int /*<<< orphan*/  SHUTDOWN_PENDING ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (struct sctp_cmd_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_auth_asoc_init_active_key (struct sctp_association*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_auth_chunk_verify (struct net*,struct sctp_chunk*,struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_chunk_free (struct sctp_chunk*) ; 
 struct sctp_chunk* sctp_make_cookie_ack (struct sctp_association*,struct sctp_chunk*) ; 
 struct sctp_chunk* sctp_make_op_error (struct sctp_association const*,struct sctp_chunk*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_process_init (struct sctp_association*,struct sctp_chunk*,int /*<<< orphan*/ ,struct sctp_init_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_sf_check_restart_addrs (struct sctp_association*,struct sctp_association const*,struct sctp_chunk*,struct sctp_cmd_seq*) ; 
 int sctp_sf_do_9_2_reshutack (struct net*,struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/ ,struct sctp_chunk*,struct sctp_cmd_seq*) ; 
 int sctp_sf_do_9_2_start_shutdown (struct net*,struct sctp_endpoint const*,struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sctp_cmd_seq*) ; 
 int /*<<< orphan*/  sctp_source (struct sctp_chunk*) ; 
 scalar_t__ sctp_sstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_state (struct sctp_association const*,int /*<<< orphan*/ ) ; 
 struct sctp_ulpevent* sctp_ulpevent_make_assoc_change (struct sctp_association const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum sctp_disposition sctp_sf_do_dupcook_a(
					struct net *net,
					const struct sctp_endpoint *ep,
					const struct sctp_association *asoc,
					struct sctp_chunk *chunk,
					struct sctp_cmd_seq *commands,
					struct sctp_association *new_asoc)
{
	struct sctp_init_chunk *peer_init;
	enum sctp_disposition disposition;
	struct sctp_ulpevent *ev;
	struct sctp_chunk *repl;
	struct sctp_chunk *err;

	/* new_asoc is a brand-new association, so these are not yet
	 * side effects--it is safe to run them here.
	 */
	peer_init = &chunk->subh.cookie_hdr->c.peer_init[0];

	if (!sctp_process_init(new_asoc, chunk, sctp_source(chunk), peer_init,
			       GFP_ATOMIC))
		goto nomem;

	if (sctp_auth_asoc_init_active_key(new_asoc, GFP_ATOMIC))
		goto nomem;

	if (!sctp_auth_chunk_verify(net, chunk, new_asoc))
		return SCTP_DISPOSITION_DISCARD;

	/* Make sure no new addresses are being added during the
	 * restart.  Though this is a pretty complicated attack
	 * since you'd have to get inside the cookie.
	 */
	if (!sctp_sf_check_restart_addrs(new_asoc, asoc, chunk, commands))
		return SCTP_DISPOSITION_CONSUME;

	/* If the endpoint is in the SHUTDOWN-ACK-SENT state and recognizes
	 * the peer has restarted (Action A), it MUST NOT setup a new
	 * association but instead resend the SHUTDOWN ACK and send an ERROR
	 * chunk with a "Cookie Received while Shutting Down" error cause to
	 * its peer.
	*/
	if (sctp_state(asoc, SHUTDOWN_ACK_SENT)) {
		disposition = sctp_sf_do_9_2_reshutack(net, ep, asoc,
				SCTP_ST_CHUNK(chunk->chunk_hdr->type),
				chunk, commands);
		if (SCTP_DISPOSITION_NOMEM == disposition)
			goto nomem;

		err = sctp_make_op_error(asoc, chunk,
					 SCTP_ERROR_COOKIE_IN_SHUTDOWN,
					 NULL, 0, 0);
		if (err)
			sctp_add_cmd_sf(commands, SCTP_CMD_REPLY,
					SCTP_CHUNK(err));

		return SCTP_DISPOSITION_CONSUME;
	}

	/* For now, stop pending T3-rtx and SACK timers, fail any unsent/unacked
	 * data. Consider the optional choice of resending of this data.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_T3_RTX_TIMERS_STOP, SCTP_NULL());
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_SACK));
	sctp_add_cmd_sf(commands, SCTP_CMD_PURGE_OUTQUEUE, SCTP_NULL());

	/* Stop pending T4-rto timer, teardown ASCONF queue, ASCONF-ACK queue
	 * and ASCONF-ACK cache.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T4_RTO));
	sctp_add_cmd_sf(commands, SCTP_CMD_PURGE_ASCONF_QUEUE, SCTP_NULL());

	repl = sctp_make_cookie_ack(new_asoc, chunk);
	if (!repl)
		goto nomem;

	/* Report association restart to upper layer. */
	ev = sctp_ulpevent_make_assoc_change(asoc, 0, SCTP_RESTART, 0,
					     new_asoc->c.sinit_num_ostreams,
					     new_asoc->c.sinit_max_instreams,
					     NULL, GFP_ATOMIC);
	if (!ev)
		goto nomem_ev;

	/* Update the content of current association. */
	sctp_add_cmd_sf(commands, SCTP_CMD_UPDATE_ASSOC, SCTP_ASOC(new_asoc));
	sctp_add_cmd_sf(commands, SCTP_CMD_EVENT_ULP, SCTP_ULPEVENT(ev));
	if (sctp_state(asoc, SHUTDOWN_PENDING) &&
	    (sctp_sstate(asoc->base.sk, CLOSING) ||
	     sock_flag(asoc->base.sk, SOCK_DEAD))) {
		/* if were currently in SHUTDOWN_PENDING, but the socket
		 * has been closed by user, don't transition to ESTABLISHED.
		 * Instead trigger SHUTDOWN bundled with COOKIE_ACK.
		 */
		sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(repl));
		return sctp_sf_do_9_2_start_shutdown(net, ep, asoc,
						     SCTP_ST_CHUNK(0), NULL,
						     commands);
	} else {
		sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
				SCTP_STATE(SCTP_STATE_ESTABLISHED));
		sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(repl));
	}
	return SCTP_DISPOSITION_CONSUME;

nomem_ev:
	sctp_chunk_free(repl);
nomem:
	return SCTP_DISPOSITION_NOMEM;
}