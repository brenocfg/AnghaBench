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
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ imm_data; } ;
struct TYPE_7__ {int wr_id; TYPE_2__ ex; struct ib_sge* sg_list; } ;
struct rds_ib_send_work {struct ib_sge* s_sge; TYPE_3__ s_wr; int /*<<< orphan*/ * s_op; } ;
struct TYPE_5__ {int w_nr; } ;
struct rds_ib_connection {TYPE_4__* i_pd; scalar_t__ i_send_hdrs_dma; TYPE_1__ i_send_ring; struct rds_ib_send_work* i_sends; } ;
struct rds_header {int dummy; } ;
struct ib_sge {int length; int /*<<< orphan*/  lkey; scalar_t__ addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  local_dma_lkey; } ;

/* Variables and functions */

void rds_ib_send_init_ring(struct rds_ib_connection *ic)
{
	struct rds_ib_send_work *send;
	u32 i;

	for (i = 0, send = ic->i_sends; i < ic->i_send_ring.w_nr; i++, send++) {
		struct ib_sge *sge;

		send->s_op = NULL;

		send->s_wr.wr_id = i;
		send->s_wr.sg_list = send->s_sge;
		send->s_wr.ex.imm_data = 0;

		sge = &send->s_sge[0];
		sge->addr = ic->i_send_hdrs_dma + (i * sizeof(struct rds_header));
		sge->length = sizeof(struct rds_header);
		sge->lkey = ic->i_pd->local_dma_lkey;

		send->s_sge[1].lkey = ic->i_pd->local_dma_lkey;
	}
}