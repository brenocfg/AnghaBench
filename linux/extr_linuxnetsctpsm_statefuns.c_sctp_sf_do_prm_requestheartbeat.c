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
struct sctp_transport {int dummy; } ;
struct sctp_endpoint {int dummy; } ;
struct sctp_cmd_seq {int dummy; } ;
struct sctp_association {int dummy; } ;
struct net {int dummy; } ;
typedef  enum sctp_disposition { ____Placeholder_sctp_disposition } sctp_disposition ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CMD_TRANSPORT_HB_SENT ; 
 int SCTP_DISPOSITION_CONSUME ; 
 scalar_t__ SCTP_DISPOSITION_NOMEM ; 
 int /*<<< orphan*/  SCTP_TRANSPORT (void*) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (struct sctp_cmd_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_sf_heartbeat (struct sctp_endpoint const*,struct sctp_association const*,union sctp_subtype const,struct sctp_transport*,struct sctp_cmd_seq*) ; 

enum sctp_disposition sctp_sf_do_prm_requestheartbeat(
					struct net *net,
					const struct sctp_endpoint *ep,
					const struct sctp_association *asoc,
					const union sctp_subtype type,
					void *arg,
					struct sctp_cmd_seq *commands)
{
	if (SCTP_DISPOSITION_NOMEM == sctp_sf_heartbeat(ep, asoc, type,
				      (struct sctp_transport *)arg, commands))
		return SCTP_DISPOSITION_NOMEM;

	/*
	 * RFC 2960 (bis), section 8.3
	 *
	 *    D) Request an on-demand HEARTBEAT on a specific destination
	 *    transport address of a given association.
	 *
	 *    The endpoint should increment the respective error  counter of
	 *    the destination transport address each time a HEARTBEAT is sent
	 *    to that address and not acknowledged within one RTO.
	 *
	 */
	sctp_add_cmd_sf(commands, SCTP_CMD_TRANSPORT_HB_SENT,
			SCTP_TRANSPORT(arg));
	return SCTP_DISPOSITION_CONSUME;
}