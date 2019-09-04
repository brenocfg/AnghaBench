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
struct sctp_association {int dummy; } ;
struct net {int dummy; } ;
typedef  enum sctp_disposition { ____Placeholder_sctp_disposition } sctp_disposition ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CMD_GEN_SACK ; 
 int SCTP_DISPOSITION_CONSUME ; 
 int /*<<< orphan*/  SCTP_FORCE () ; 
 int /*<<< orphan*/  SCTP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_MIB_DELAY_SACK_EXPIREDS ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (struct sctp_cmd_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

enum sctp_disposition sctp_sf_do_6_2_sack(struct net *net,
					  const struct sctp_endpoint *ep,
					  const struct sctp_association *asoc,
					  const union sctp_subtype type,
					  void *arg,
					  struct sctp_cmd_seq *commands)
{
	SCTP_INC_STATS(net, SCTP_MIB_DELAY_SACK_EXPIREDS);
	sctp_add_cmd_sf(commands, SCTP_CMD_GEN_SACK, SCTP_FORCE());
	return SCTP_DISPOSITION_CONSUME;
}