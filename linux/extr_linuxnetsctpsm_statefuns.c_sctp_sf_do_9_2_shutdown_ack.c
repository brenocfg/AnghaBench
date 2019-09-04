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
typedef  union sctp_subtype {int dummy; } sctp_subtype ;
struct sctp_shutdown_chunk {int dummy; } ;
struct sctp_endpoint {int dummy; } ;
struct sctp_cmd_seq {int dummy; } ;
struct sctp_chunk {int dummy; } ;
struct sctp_association {scalar_t__* timeouts; } ;
struct net {int dummy; } ;
typedef  enum sctp_disposition { ____Placeholder_sctp_disposition } sctp_disposition ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CHUNK (struct sctp_chunk*) ; 
 int /*<<< orphan*/  SCTP_CMD_HB_TIMERS_STOP ; 
 int /*<<< orphan*/  SCTP_CMD_NEW_STATE ; 
 int /*<<< orphan*/  SCTP_CMD_REPLY ; 
 int /*<<< orphan*/  SCTP_CMD_SETUP_T2 ; 
 int /*<<< orphan*/  SCTP_CMD_TIMER_RESTART ; 
 int /*<<< orphan*/  SCTP_CMD_TIMER_STOP ; 
 int SCTP_DISPOSITION_CONSUME ; 
 int SCTP_DISPOSITION_NOMEM ; 
 size_t SCTP_EVENT_TIMEOUT_AUTOCLOSE ; 
 size_t SCTP_EVENT_TIMEOUT_T2_SHUTDOWN ; 
 int /*<<< orphan*/  SCTP_NULL () ; 
 int /*<<< orphan*/  SCTP_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_STATE_SHUTDOWN_ACK_SENT ; 
 int /*<<< orphan*/  SCTP_TO (size_t) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (struct sctp_cmd_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_chunk_length_valid (struct sctp_chunk*,int) ; 
 struct sctp_chunk* sctp_make_shutdown_ack (struct sctp_association const*,struct sctp_chunk*) ; 
 int sctp_sf_pdiscard (struct net*,struct sctp_endpoint const*,struct sctp_association const*,union sctp_subtype const,void*,struct sctp_cmd_seq*) ; 
 int sctp_sf_violation_chunklen (struct net*,struct sctp_endpoint const*,struct sctp_association const*,union sctp_subtype const,void*,struct sctp_cmd_seq*) ; 
 int /*<<< orphan*/  sctp_vtag_verify (struct sctp_chunk*,struct sctp_association const*) ; 

enum sctp_disposition sctp_sf_do_9_2_shutdown_ack(
					struct net *net,
					const struct sctp_endpoint *ep,
					const struct sctp_association *asoc,
					const union sctp_subtype type,
					void *arg,
					struct sctp_cmd_seq *commands)
{
	struct sctp_chunk *chunk = arg;
	struct sctp_chunk *reply;

	/* There are 2 ways of getting here:
	 *    1) called in response to a SHUTDOWN chunk
	 *    2) called when SCTP_EVENT_NO_PENDING_TSN event is issued.
	 *
	 * For the case (2), the arg parameter is set to NULL.  We need
	 * to check that we have a chunk before accessing it's fields.
	 */
	if (chunk) {
		if (!sctp_vtag_verify(chunk, asoc))
			return sctp_sf_pdiscard(net, ep, asoc, type, arg,
						commands);

		/* Make sure that the SHUTDOWN chunk has a valid length. */
		if (!sctp_chunk_length_valid(
				chunk, sizeof(struct sctp_shutdown_chunk)))
			return sctp_sf_violation_chunklen(net, ep, asoc, type,
							  arg, commands);
	}

	/* If it has no more outstanding DATA chunks, the SHUTDOWN receiver
	 * shall send a SHUTDOWN ACK ...
	 */
	reply = sctp_make_shutdown_ack(asoc, chunk);
	if (!reply)
		goto nomem;

	/* Set the transport for the SHUTDOWN ACK chunk and the timeout for
	 * the T2-shutdown timer.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_SETUP_T2, SCTP_CHUNK(reply));

	/* and start/restart a T2-shutdown timer of its own, */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T2_SHUTDOWN));

	if (asoc->timeouts[SCTP_EVENT_TIMEOUT_AUTOCLOSE])
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
				SCTP_TO(SCTP_EVENT_TIMEOUT_AUTOCLOSE));

	/* Enter the SHUTDOWN-ACK-SENT state.  */
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_SHUTDOWN_ACK_SENT));

	/* sctp-implguide 2.10 Issues with Heartbeating and failover
	 *
	 * HEARTBEAT ... is discontinued after sending either SHUTDOWN
	 * or SHUTDOWN-ACK.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_HB_TIMERS_STOP, SCTP_NULL());

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(reply));

	return SCTP_DISPOSITION_CONSUME;

nomem:
	return SCTP_DISPOSITION_NOMEM;
}