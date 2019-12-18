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
struct TYPE_6__ {int /*<<< orphan*/  rmb_desc; struct smc_link_group* lgr; } ;
struct smc_sock {TYPE_2__ conn; TYPE_1__* clcsock; } ;
struct smc_link_group {struct smc_link* lnk; } ;
struct smc_link {int ibport; int /*<<< orphan*/  gid; TYPE_3__* smcibdev; int /*<<< orphan*/  llc_add; scalar_t__ llc_confirm_rc; int /*<<< orphan*/  llc_confirm; } ;
struct smc_clc_msg_decline {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  sysctl_tcp_keepalive_time; } ;
struct net {TYPE_4__ ipv4; } ;
typedef  int /*<<< orphan*/  dclc ;
struct TYPE_7__ {int /*<<< orphan*/ * mac; } ;
struct TYPE_5__ {int /*<<< orphan*/  sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLC_WAIT_TIME_SHORT ; 
 int EAGAIN ; 
 int /*<<< orphan*/  SMC_CLC_DECLINE ; 
 int SMC_CLC_DECL_ERR_RDYLNK ; 
 int SMC_CLC_DECL_ERR_REGRMB ; 
 int SMC_CLC_DECL_RMBE_EC ; 
 int SMC_CLC_DECL_TIMEOUT_AL ; 
 int SMC_CLC_DECL_TIMEOUT_CL ; 
 int /*<<< orphan*/  SMC_LLC_RESP ; 
 int /*<<< orphan*/  SMC_LLC_WAIT_FIRST_TIME ; 
 int /*<<< orphan*/  SMC_LLC_WAIT_TIME ; 
 size_t SMC_SINGLE_LINK ; 
 int smc_clc_wait_msg (struct smc_sock*,struct smc_clc_msg_decline*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smc_ib_modify_qp_rts (struct smc_link*) ; 
 int /*<<< orphan*/  smc_llc_link_active (struct smc_link*,int /*<<< orphan*/ ) ; 
 int smc_llc_send_add_link (struct smc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smc_llc_send_confirm_link (struct smc_link*,int /*<<< orphan*/ ) ; 
 scalar_t__ smc_reg_rmb (struct smc_link*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smc_wr_remember_qp_attr (struct smc_link*) ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 
 int wait_for_completion_interruptible_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smc_clnt_conf_first_link(struct smc_sock *smc)
{
	struct net *net = sock_net(smc->clcsock->sk);
	struct smc_link_group *lgr = smc->conn.lgr;
	struct smc_link *link;
	int rest;
	int rc;

	link = &lgr->lnk[SMC_SINGLE_LINK];
	/* receive CONFIRM LINK request from server over RoCE fabric */
	rest = wait_for_completion_interruptible_timeout(
		&link->llc_confirm,
		SMC_LLC_WAIT_FIRST_TIME);
	if (rest <= 0) {
		struct smc_clc_msg_decline dclc;

		rc = smc_clc_wait_msg(smc, &dclc, sizeof(dclc),
				      SMC_CLC_DECLINE, CLC_WAIT_TIME_SHORT);
		return rc == -EAGAIN ? SMC_CLC_DECL_TIMEOUT_CL : rc;
	}

	if (link->llc_confirm_rc)
		return SMC_CLC_DECL_RMBE_EC;

	rc = smc_ib_modify_qp_rts(link);
	if (rc)
		return SMC_CLC_DECL_ERR_RDYLNK;

	smc_wr_remember_qp_attr(link);

	if (smc_reg_rmb(link, smc->conn.rmb_desc, false))
		return SMC_CLC_DECL_ERR_REGRMB;

	/* send CONFIRM LINK response over RoCE fabric */
	rc = smc_llc_send_confirm_link(link, SMC_LLC_RESP);
	if (rc < 0)
		return SMC_CLC_DECL_TIMEOUT_CL;

	/* receive ADD LINK request from server over RoCE fabric */
	rest = wait_for_completion_interruptible_timeout(&link->llc_add,
							 SMC_LLC_WAIT_TIME);
	if (rest <= 0) {
		struct smc_clc_msg_decline dclc;

		rc = smc_clc_wait_msg(smc, &dclc, sizeof(dclc),
				      SMC_CLC_DECLINE, CLC_WAIT_TIME_SHORT);
		return rc == -EAGAIN ? SMC_CLC_DECL_TIMEOUT_AL : rc;
	}

	/* send add link reject message, only one link supported for now */
	rc = smc_llc_send_add_link(link,
				   link->smcibdev->mac[link->ibport - 1],
				   link->gid, SMC_LLC_RESP);
	if (rc < 0)
		return SMC_CLC_DECL_TIMEOUT_AL;

	smc_llc_link_active(link, net->ipv4.sysctl_tcp_keepalive_time);

	return 0;
}