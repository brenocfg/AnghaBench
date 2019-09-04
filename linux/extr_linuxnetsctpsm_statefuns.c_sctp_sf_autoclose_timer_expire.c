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
struct sctp_association {int /*<<< orphan*/  outqueue; } ;
struct net {int dummy; } ;
typedef  enum sctp_disposition { ____Placeholder_sctp_disposition } sctp_disposition ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CMD_NEW_STATE ; 
 int SCTP_DISPOSITION_CONSUME ; 
 int /*<<< orphan*/  SCTP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_MIB_AUTOCLOSE_EXPIREDS ; 
 int /*<<< orphan*/  SCTP_STATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_STATE_SHUTDOWN_PENDING ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (struct sctp_cmd_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_outq_is_empty (int /*<<< orphan*/ *) ; 
 int sctp_sf_do_9_2_start_shutdown (struct net*,struct sctp_endpoint const*,struct sctp_association const*,union sctp_subtype const,void*,struct sctp_cmd_seq*) ; 

enum sctp_disposition sctp_sf_autoclose_timer_expire(
					struct net *net,
					const struct sctp_endpoint *ep,
					const struct sctp_association *asoc,
					const union sctp_subtype type,
					void *arg,
					struct sctp_cmd_seq *commands)
{
	enum sctp_disposition disposition;

	SCTP_INC_STATS(net, SCTP_MIB_AUTOCLOSE_EXPIREDS);

	/* From 9.2 Shutdown of an Association
	 * Upon receipt of the SHUTDOWN primitive from its upper
	 * layer, the endpoint enters SHUTDOWN-PENDING state and
	 * remains there until all outstanding data has been
	 * acknowledged by its peer. The endpoint accepts no new data
	 * from its upper layer, but retransmits data to the far end
	 * if necessary to fill gaps.
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_NEW_STATE,
			SCTP_STATE(SCTP_STATE_SHUTDOWN_PENDING));

	disposition = SCTP_DISPOSITION_CONSUME;
	if (sctp_outq_is_empty(&asoc->outqueue)) {
		disposition = sctp_sf_do_9_2_start_shutdown(net, ep, asoc, type,
							    arg, commands);
	}

	return disposition;
}