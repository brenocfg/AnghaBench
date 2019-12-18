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
struct smc_link_group {TYPE_1__** rtokens; struct smc_link* lnk; } ;
struct smc_link {int /*<<< orphan*/  roce_qp; } ;
struct TYPE_6__ {int peer_conn_abort; } ;
struct TYPE_7__ {TYPE_2__ conn_state_flags; } ;
struct smc_connection {size_t rtoken_idx; TYPE_3__ local_tx_ctrl; scalar_t__ tx_off; struct smc_link_group* lgr; } ;
struct TYPE_8__ {int num_sge; int /*<<< orphan*/  wr_id; } ;
struct ib_rdma_wr {TYPE_4__ wr; int /*<<< orphan*/  rkey; scalar_t__ remote_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  rkey; scalar_t__ dma_addr; } ;

/* Variables and functions */
 size_t SMC_SINGLE_LINK ; 
 int ib_post_send (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_lgr_terminate (struct smc_link_group*) ; 
 int /*<<< orphan*/  smc_wr_tx_get_next_wr_id (struct smc_link*) ; 

__attribute__((used)) static int smc_tx_rdma_write(struct smc_connection *conn, int peer_rmbe_offset,
			     int num_sges, struct ib_rdma_wr *rdma_wr)
{
	struct smc_link_group *lgr = conn->lgr;
	struct smc_link *link;
	int rc;

	link = &lgr->lnk[SMC_SINGLE_LINK];
	rdma_wr->wr.wr_id = smc_wr_tx_get_next_wr_id(link);
	rdma_wr->wr.num_sge = num_sges;
	rdma_wr->remote_addr =
		lgr->rtokens[conn->rtoken_idx][SMC_SINGLE_LINK].dma_addr +
		/* RMBE within RMB */
		conn->tx_off +
		/* offset within RMBE */
		peer_rmbe_offset;
	rdma_wr->rkey = lgr->rtokens[conn->rtoken_idx][SMC_SINGLE_LINK].rkey;
	rc = ib_post_send(link->roce_qp, &rdma_wr->wr, NULL);
	if (rc) {
		conn->local_tx_ctrl.conn_state_flags.peer_conn_abort = 1;
		smc_lgr_terminate(lgr);
	}
	return rc;
}