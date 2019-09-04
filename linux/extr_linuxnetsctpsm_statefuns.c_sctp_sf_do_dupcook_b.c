#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sctp_init_chunk {int dummy; } ;
struct sctp_endpoint {int dummy; } ;
struct sctp_cmd_seq {int dummy; } ;
struct TYPE_7__ {TYPE_2__* cookie_hdr; } ;
struct sctp_chunk {TYPE_3__ subh; } ;
struct TYPE_8__ {int /*<<< orphan*/  auth_capable; scalar_t__ adaptation_ind; } ;
struct sctp_association {TYPE_4__ peer; } ;
struct net {int dummy; } ;
typedef  enum sctp_disposition { ____Placeholder_sctp_disposition } sctp_disposition ;
struct TYPE_5__ {struct sctp_init_chunk* peer_init; } ;
struct TYPE_6__ {TYPE_1__ c; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_ASOC (struct sctp_association*) ; 
 int /*<<< orphan*/  SCTP_CHUNK (struct sctp_chunk*) ; 
 int /*<<< orphan*/  SCTP_CMD_ADAPTATION_IND ; 
 int /*<<< orphan*/  SCTP_CMD_ASSOC_CHANGE ; 
 int /*<<< orphan*/  SCTP_CMD_HB_TIMERS_START ; 
 int /*<<< orphan*/  SCTP_CMD_NEW_STATE ; 
 int /*<<< orphan*/  SCTP_CMD_PEER_NO_AUTH ; 
 int /*<<< orphan*/  SCTP_CMD_REPLY ; 
 int /*<<< orphan*/  SCTP_CMD_UPDATE_ASSOC ; 
 int /*<<< orphan*/  SCTP_COMM_UP ; 
 int SCTP_DISPOSITION_CONSUME ; 
 int SCTP_DISPOSITION_DISCARD ; 
 int SCTP_DISPOSITION_NOMEM ; 
 int /*<<< orphan*/  SCTP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_MIB_CURRESTAB ; 
 int /*<<< orphan*/  SCTP_NULL () ; 
 int /*<<< orphan*/  SCTP_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_STATE_ESTABLISHED ; 
 int /*<<< orphan*/  SCTP_U8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (struct sctp_cmd_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_auth_asoc_init_active_key (struct sctp_association*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_auth_chunk_verify (struct net*,struct sctp_chunk*,struct sctp_association*) ; 
 struct sctp_chunk* sctp_make_cookie_ack (struct sctp_association*,struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_process_init (struct sctp_association*,struct sctp_chunk*,int /*<<< orphan*/ ,struct sctp_init_chunk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_source (struct sctp_chunk*) ; 

__attribute__((used)) static enum sctp_disposition sctp_sf_do_dupcook_b(
					struct net *net,
					const struct sctp_endpoint *ep,
					const struct sctp_association *asoc,
					struct sctp_chunk *chunk,
					struct sctp_cmd_seq *commands,
					struct sctp_association *new_asoc)
{
	struct sctp_init_chunk *peer_init;
	struct sctp_chunk *repl;

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

	/* Update the content of current association.  */
	sctp_add_cmd_sf(commands, SCTP_CMD_UPDATE_ASSOC, SCTP_ASOC(new_asoc));
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_ESTABLISHED));
	SCTP_INC_STATS(net, SCTP_MIB_CURRESTAB);
	sctp_add_cmd_sf(commands, SCTP_CMD_HB_TIMERS_START, SCTP_NULL());

	repl = sctp_make_cookie_ack(new_asoc, chunk);
	if (!repl)
		goto nomem;

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(repl));

	/* RFC 2960 5.1 Normal Establishment of an Association
	 *
	 * D) IMPLEMENTATION NOTE: An implementation may choose to
	 * send the Communication Up notification to the SCTP user
	 * upon reception of a valid COOKIE ECHO chunk.
	 *
	 * Sadly, this needs to be implemented as a side-effect, because
	 * we are not guaranteed to have set the association id of the real
	 * association and so these notifications need to be delayed until
	 * the association id is allocated.
	 */

	sctp_add_cmd_sf(commands, SCTP_CMD_ASSOC_CHANGE, SCTP_U8(SCTP_COMM_UP));

	/* Sockets API Draft Section 5.3.1.6
	 * When a peer sends a Adaptation Layer Indication parameter , SCTP
	 * delivers this notification to inform the application that of the
	 * peers requested adaptation layer.
	 *
	 * This also needs to be done as a side effect for the same reason as
	 * above.
	 */
	if (asoc->peer.adaptation_ind)
		sctp_add_cmd_sf(commands, SCTP_CMD_ADAPTATION_IND, SCTP_NULL());

	if (!asoc->peer.auth_capable)
		sctp_add_cmd_sf(commands, SCTP_CMD_PEER_NO_AUTH, SCTP_NULL());

	return SCTP_DISPOSITION_CONSUME;

nomem:
	return SCTP_DISPOSITION_NOMEM;
}