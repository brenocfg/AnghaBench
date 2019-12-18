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
struct ib_sge {int length; int /*<<< orphan*/  lkey; int /*<<< orphan*/  addr; } ;
struct ib_send_wr {int num_sge; int send_flags; int /*<<< orphan*/  wr_id; int /*<<< orphan*/  opcode; struct ib_sge* sg_list; } ;
struct rds_ib_connection {TYPE_1__* i_pd; int /*<<< orphan*/  i_ack_dma; struct ib_sge i_ack_sge; struct ib_send_wr i_ack_wr; } ;
struct rds_header {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  local_dma_lkey; } ;

/* Variables and functions */
 int IB_SEND_SIGNALED ; 
 int IB_SEND_SOLICITED ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 int /*<<< orphan*/  RDS_IB_ACK_WR_ID ; 

void rds_ib_recv_init_ack(struct rds_ib_connection *ic)
{
	struct ib_send_wr *wr = &ic->i_ack_wr;
	struct ib_sge *sge = &ic->i_ack_sge;

	sge->addr = ic->i_ack_dma;
	sge->length = sizeof(struct rds_header);
	sge->lkey = ic->i_pd->local_dma_lkey;

	wr->sg_list = sge;
	wr->num_sge = 1;
	wr->opcode = IB_WR_SEND;
	wr->wr_id = RDS_IB_ACK_WR_ID;
	wr->send_flags = IB_SEND_SIGNALED | IB_SEND_SOLICITED;
}