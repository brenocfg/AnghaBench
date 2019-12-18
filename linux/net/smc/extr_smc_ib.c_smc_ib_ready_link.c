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
struct smc_link_group {scalar_t__ role; } ;
struct smc_link {TYPE_1__* smcibdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  roce_cq_recv; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_CQ_SOLICITED_MASK ; 
 scalar_t__ SMC_SERV ; 
 int ib_req_notify_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct smc_link_group* smc_get_lgr (struct smc_link*) ; 
 int smc_ib_modify_qp_init (struct smc_link*) ; 
 int smc_ib_modify_qp_rtr (struct smc_link*) ; 
 int smc_ib_modify_qp_rts (struct smc_link*) ; 
 int /*<<< orphan*/  smc_wr_remember_qp_attr (struct smc_link*) ; 
 int smc_wr_rx_post_init (struct smc_link*) ; 

int smc_ib_ready_link(struct smc_link *lnk)
{
	struct smc_link_group *lgr = smc_get_lgr(lnk);
	int rc = 0;

	rc = smc_ib_modify_qp_init(lnk);
	if (rc)
		goto out;

	rc = smc_ib_modify_qp_rtr(lnk);
	if (rc)
		goto out;
	smc_wr_remember_qp_attr(lnk);
	rc = ib_req_notify_cq(lnk->smcibdev->roce_cq_recv,
			      IB_CQ_SOLICITED_MASK);
	if (rc)
		goto out;
	rc = smc_wr_rx_post_init(lnk);
	if (rc)
		goto out;
	smc_wr_remember_qp_attr(lnk);

	if (lgr->role == SMC_SERV) {
		rc = smc_ib_modify_qp_rts(lnk);
		if (rc)
			goto out;
		smc_wr_remember_qp_attr(lnk);
	}
out:
	return rc;
}