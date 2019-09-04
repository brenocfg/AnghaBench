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
struct smc_link {int /*<<< orphan*/  roce_qp; int /*<<< orphan*/  psn_initial; } ;
struct ib_qp_attr {int max_rd_atomic; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  timeout; int /*<<< orphan*/  qp_state; } ;
typedef  int /*<<< orphan*/  qp_attr ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPS_RTS ; 
 int IB_QP_MAX_QP_RD_ATOMIC ; 
 int IB_QP_RETRY_CNT ; 
 int IB_QP_RNR_RETRY ; 
 int IB_QP_SQ_PSN ; 
 int IB_QP_STATE ; 
 int IB_QP_TIMEOUT ; 
 int /*<<< orphan*/  SMC_QP_RETRY_CNT ; 
 int /*<<< orphan*/  SMC_QP_RNR_RETRY ; 
 int /*<<< orphan*/  SMC_QP_TIMEOUT ; 
 int ib_modify_qp (int /*<<< orphan*/ ,struct ib_qp_attr*,int) ; 
 int /*<<< orphan*/  memset (struct ib_qp_attr*,int /*<<< orphan*/ ,int) ; 

int smc_ib_modify_qp_rts(struct smc_link *lnk)
{
	struct ib_qp_attr qp_attr;

	memset(&qp_attr, 0, sizeof(qp_attr));
	qp_attr.qp_state = IB_QPS_RTS;
	qp_attr.timeout = SMC_QP_TIMEOUT;	/* local ack timeout */
	qp_attr.retry_cnt = SMC_QP_RETRY_CNT;	/* retry count */
	qp_attr.rnr_retry = SMC_QP_RNR_RETRY;	/* RNR retries, 7=infinite */
	qp_attr.sq_psn = lnk->psn_initial;	/* starting send packet seq # */
	qp_attr.max_rd_atomic = 1;	/* # of outstanding RDMA reads and
					 * atomic ops allowed
					 */
	return ib_modify_qp(lnk->roce_qp, &qp_attr,
			    IB_QP_STATE | IB_QP_TIMEOUT | IB_QP_RETRY_CNT |
			    IB_QP_SQ_PSN | IB_QP_RNR_RETRY |
			    IB_QP_MAX_QP_RD_ATOMIC);
}