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
 int /*<<< orphan*/  SCTP_CMD_TIMER_START ; 
 int /*<<< orphan*/  SCTP_CMD_TIMER_STOP ; 
 int SCTP_DISPOSITION_CONSUME ; 
 int SCTP_DISPOSITION_NOMEM ; 
 size_t SCTP_EVENT_TIMEOUT_AUTOCLOSE ; 
 size_t SCTP_EVENT_TIMEOUT_T2_SHUTDOWN ; 
 size_t SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD ; 
 int /*<<< orphan*/  SCTP_NULL () ; 
 int /*<<< orphan*/  SCTP_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_STATE_SHUTDOWN_SENT ; 
 int /*<<< orphan*/  SCTP_TO (size_t) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (struct sctp_cmd_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_chunk* sctp_make_shutdown (struct sctp_association const*,int /*<<< orphan*/ *) ; 

enum sctp_disposition sctp_sf_do_9_2_start_shutdown(
					struct net *net,
					const struct sctp_endpoint *ep,
					const struct sctp_association *asoc,
					const union sctp_subtype type,
					void *arg,
					struct sctp_cmd_seq *commands)
{
	struct sctp_chunk *reply;

	/* Once all its outstanding data has been acknowledged, the
	 * endpoint shall send a SHUTDOWN chunk to its peer including
	 * in the Cumulative TSN Ack field the last sequential TSN it
	 * has received from the peer.
	 */
	reply = sctp_make_shutdown(asoc, NULL);
	if (!reply)
		goto nomem;

	/* Set the transport for the SHUTDOWN chunk and the timeout for the
	 * T2-shutdown timer.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_SETUP_T2, SCTP_CHUNK(reply));

	/* It shall then start the T2-shutdown timer */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_START,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T2_SHUTDOWN));

	/* RFC 4960 Section 9.2
	 * The sender of the SHUTDOWN MAY also start an overall guard timer
	 * 'T5-shutdown-guard' to bound the overall time for shutdown sequence.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T5_SHUTDOWN_GUARD));

	if (asoc->timeouts[SCTP_EVENT_TIMEOUT_AUTOCLOSE])
		sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_STOP,
				SCTP_TO(SCTP_EVENT_TIMEOUT_AUTOCLOSE));

	/* and enter the SHUTDOWN-SENT state.  */
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_SHUTDOWN_SENT));

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