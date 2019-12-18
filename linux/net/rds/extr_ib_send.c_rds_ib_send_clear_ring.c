#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int opcode; } ;
struct rds_ib_send_work {TYPE_2__ s_wr; scalar_t__ s_op; } ;
struct TYPE_3__ {scalar_t__ w_nr; } ;
struct rds_ib_connection {TYPE_1__ i_send_ring; struct rds_ib_send_work* i_sends; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  rds_ib_send_unmap_op (struct rds_ib_connection*,struct rds_ib_send_work*,int /*<<< orphan*/ ) ; 

void rds_ib_send_clear_ring(struct rds_ib_connection *ic)
{
	struct rds_ib_send_work *send;
	u32 i;

	for (i = 0, send = ic->i_sends; i < ic->i_send_ring.w_nr; i++, send++) {
		if (send->s_op && send->s_wr.opcode != 0xdead)
			rds_ib_send_unmap_op(ic, send, IB_WC_WR_FLUSH_ERR);
	}
}