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
struct sctp_chunkhdr {int dummy; } ;
struct sctp_chunk {int dummy; } ;
struct sctp_association {int dummy; } ;
struct net {int dummy; } ;
typedef  enum sctp_disposition { ____Placeholder_sctp_disposition } sctp_disposition ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CHUNK (struct sctp_chunk*) ; 
 int /*<<< orphan*/  SCTP_CMD_REPLY ; 
 int /*<<< orphan*/  SCTP_CMD_SETUP_T2 ; 
 int /*<<< orphan*/  SCTP_CMD_TIMER_RESTART ; 
 int SCTP_DISPOSITION_CONSUME ; 
 int SCTP_DISPOSITION_NOMEM ; 
 int /*<<< orphan*/  SCTP_EVENT_TIMEOUT_T2_SHUTDOWN ; 
 int /*<<< orphan*/  SCTP_TO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (struct sctp_cmd_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_chunk_length_valid (struct sctp_chunk*,int) ; 
 struct sctp_chunk* sctp_make_shutdown_ack (struct sctp_association const*,struct sctp_chunk*) ; 
 int sctp_sf_violation_chunklen (struct net*,struct sctp_endpoint const*,struct sctp_association const*,union sctp_subtype const,void*,struct sctp_cmd_seq*) ; 

enum sctp_disposition sctp_sf_do_9_2_reshutack(
					struct net *net,
					const struct sctp_endpoint *ep,
					const struct sctp_association *asoc,
					const union sctp_subtype type,
					void *arg,
					struct sctp_cmd_seq *commands)
{
	struct sctp_chunk *chunk = arg;
	struct sctp_chunk *reply;

	/* Make sure that the chunk has a valid length */
	if (!sctp_chunk_length_valid(chunk, sizeof(struct sctp_chunkhdr)))
		return sctp_sf_violation_chunklen(net, ep, asoc, type, arg,
						  commands);

	/* Since we are not going to really process this INIT, there
	 * is no point in verifying chunk boundries.  Just generate
	 * the SHUTDOWN ACK.
	 */
	reply = sctp_make_shutdown_ack(asoc, chunk);
	if (NULL == reply)
		goto nomem;

	/* Set the transport for the SHUTDOWN ACK chunk and the timeout for
	 * the T2-SHUTDOWN timer.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_SETUP_T2, SCTP_CHUNK(reply));

	/* and restart the T2-shutdown timer. */
	sctp_add_cmd_sf(commands, SCTP_CMD_TIMER_RESTART,
			SCTP_TO(SCTP_EVENT_TIMEOUT_T2_SHUTDOWN));

	sctp_add_cmd_sf(commands, SCTP_CMD_REPLY, SCTP_CHUNK(reply));

	return SCTP_DISPOSITION_CONSUME;
nomem:
	return SCTP_DISPOSITION_NOMEM;
}