#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sctp_cmd_seq {int dummy; } ;
struct sctp_chunk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;
struct sctp_association {int /*<<< orphan*/  ep; int /*<<< orphan*/  state; TYPE_1__ base; int /*<<< orphan*/  outqueue; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SCTP_EVENT_NO_PENDING_TSN ; 
 int /*<<< orphan*/  SCTP_EVENT_T_OTHER ; 
 int /*<<< orphan*/  SCTP_ST_OTHER (int /*<<< orphan*/ ) ; 
 int sctp_do_sm (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sctp_association*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sctp_outq_sack (int /*<<< orphan*/ *,struct sctp_chunk*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sctp_cmd_process_sack(struct sctp_cmd_seq *cmds,
				 struct sctp_association *asoc,
				 struct sctp_chunk *chunk)
{
	int err = 0;

	if (sctp_outq_sack(&asoc->outqueue, chunk)) {
		struct net *net = sock_net(asoc->base.sk);

		/* There are no more TSNs awaiting SACK.  */
		err = sctp_do_sm(net, SCTP_EVENT_T_OTHER,
				 SCTP_ST_OTHER(SCTP_EVENT_NO_PENDING_TSN),
				 asoc->state, asoc->ep, asoc, NULL,
				 GFP_ATOMIC);
	}

	return err;
}