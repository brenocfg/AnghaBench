#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct smc_link {int /*<<< orphan*/  roce_qp; int /*<<< orphan*/  peer_psn; int /*<<< orphan*/  peer_qpn; int /*<<< orphan*/  peer_mac; int /*<<< orphan*/  peer_gid; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  ibport; int /*<<< orphan*/  peer_mtu; int /*<<< orphan*/  path_mtu; } ;
struct TYPE_5__ {int /*<<< orphan*/  dmac; } ;
struct TYPE_6__ {TYPE_1__ roce; int /*<<< orphan*/  type; } ;
struct ib_qp_attr {int max_dest_rd_atomic; int /*<<< orphan*/  min_rnr_timer; int /*<<< orphan*/  rq_psn; int /*<<< orphan*/  dest_qp_num; TYPE_2__ ah_attr; int /*<<< orphan*/  path_mtu; int /*<<< orphan*/  qp_state; } ;
typedef  int /*<<< orphan*/  qp_attr ;
typedef  enum ib_qp_attr_mask { ____Placeholder_ib_qp_attr_mask } ib_qp_attr_mask ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPS_RTR ; 
 int IB_QP_AV ; 
 int IB_QP_DEST_QPN ; 
 int IB_QP_MAX_DEST_RD_ATOMIC ; 
 int IB_QP_MIN_RNR_TIMER ; 
 int IB_QP_PATH_MTU ; 
 int IB_QP_RQ_PSN ; 
 int IB_QP_STATE ; 
 int /*<<< orphan*/  RDMA_AH_ATTR_TYPE_ROCE ; 
 int /*<<< orphan*/  SMC_QP_MIN_RNR_TIMER ; 
 int ib_modify_qp (int /*<<< orphan*/ ,struct ib_qp_attr*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ib_qp_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_dgid_raw (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_grh (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_port_num (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smc_ib_modify_qp_rtr(struct smc_link *lnk)
{
	enum ib_qp_attr_mask qp_attr_mask =
		IB_QP_STATE | IB_QP_AV | IB_QP_PATH_MTU | IB_QP_DEST_QPN |
		IB_QP_RQ_PSN | IB_QP_MAX_DEST_RD_ATOMIC | IB_QP_MIN_RNR_TIMER;
	struct ib_qp_attr qp_attr;

	memset(&qp_attr, 0, sizeof(qp_attr));
	qp_attr.qp_state = IB_QPS_RTR;
	qp_attr.path_mtu = min(lnk->path_mtu, lnk->peer_mtu);
	qp_attr.ah_attr.type = RDMA_AH_ATTR_TYPE_ROCE;
	rdma_ah_set_port_num(&qp_attr.ah_attr, lnk->ibport);
	rdma_ah_set_grh(&qp_attr.ah_attr, NULL, 0, lnk->sgid_index, 1, 0);
	rdma_ah_set_dgid_raw(&qp_attr.ah_attr, lnk->peer_gid);
	memcpy(&qp_attr.ah_attr.roce.dmac, lnk->peer_mac,
	       sizeof(lnk->peer_mac));
	qp_attr.dest_qp_num = lnk->peer_qpn;
	qp_attr.rq_psn = lnk->peer_psn; /* starting receive packet seq # */
	qp_attr.max_dest_rd_atomic = 1; /* max # of resources for incoming
					 * requests
					 */
	qp_attr.min_rnr_timer = SMC_QP_MIN_RNR_TIMER;

	return ib_modify_qp(lnk->roce_qp, &qp_attr, qp_attr_mask);
}