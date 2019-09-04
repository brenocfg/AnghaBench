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
struct sctp_errhdr {int dummy; } ;
struct sctp_cmd_seq {int dummy; } ;
struct sctp_chunk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;
struct sctp_association {TYPE_1__ base; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNABORTED ; 
 int /*<<< orphan*/  SCTP_CHUNK (struct sctp_chunk*) ; 
 int /*<<< orphan*/  SCTP_CMD_ASSOC_FAILED ; 
 int /*<<< orphan*/  SCTP_CMD_REPLY ; 
 int /*<<< orphan*/  SCTP_CMD_SET_SK_ERR ; 
 int /*<<< orphan*/  SCTP_DEC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_ERROR_RSRC_LOW ; 
 int /*<<< orphan*/  SCTP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_MIB_ABORTEDS ; 
 int /*<<< orphan*/  SCTP_MIB_CURRESTAB ; 
 int /*<<< orphan*/  SCTP_PERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_add_cmd_sf (struct sctp_cmd_seq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_assoc_update (struct sctp_association*,struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_init_cause (struct sctp_chunk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sctp_chunk* sctp_make_abort (struct sctp_association*,int /*<<< orphan*/ *,int) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sctp_cmd_assoc_update(struct sctp_cmd_seq *cmds,
				  struct sctp_association *asoc,
				  struct sctp_association *new)
{
	struct net *net = sock_net(asoc->base.sk);
	struct sctp_chunk *abort;

	if (!sctp_assoc_update(asoc, new))
		return;

	abort = sctp_make_abort(asoc, NULL, sizeof(struct sctp_errhdr));
	if (abort) {
		sctp_init_cause(abort, SCTP_ERROR_RSRC_LOW, 0);
		sctp_add_cmd_sf(cmds, SCTP_CMD_REPLY, SCTP_CHUNK(abort));
	}
	sctp_add_cmd_sf(cmds, SCTP_CMD_SET_SK_ERR, SCTP_ERROR(ECONNABORTED));
	sctp_add_cmd_sf(cmds, SCTP_CMD_ASSOC_FAILED,
			SCTP_PERR(SCTP_ERROR_RSRC_LOW));
	SCTP_INC_STATS(net, SCTP_MIB_ABORTEDS);
	SCTP_DEC_STATS(net, SCTP_MIB_CURRESTAB);
}