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
struct TYPE_4__ {scalar_t__ w_nr; } ;
struct rds_ib_connection {TYPE_2__ i_send_ring; } ;
struct TYPE_3__ {int /*<<< orphan*/  imm_data; } ;
struct ib_wc {scalar_t__ wr_id; TYPE_1__ ex; int /*<<< orphan*/  byte_len; int /*<<< orphan*/  status; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 scalar_t__ RDS_IB_ACK_WR_ID ; 
 int /*<<< orphan*/  RDS_IB_WC_MAX ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int ib_poll_cq (struct ib_cq*,int /*<<< orphan*/ ,struct ib_wc*) ; 
 int /*<<< orphan*/  rds_ib_mr_cqe_handler (struct rds_ib_connection*,struct ib_wc*) ; 
 int /*<<< orphan*/  rds_ib_send_cqe_handler (struct rds_ib_connection*,struct ib_wc*) ; 
 int /*<<< orphan*/  rdsdebug (char*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void poll_scq(struct rds_ib_connection *ic, struct ib_cq *cq,
		     struct ib_wc *wcs)
{
	int nr, i;
	struct ib_wc *wc;

	while ((nr = ib_poll_cq(cq, RDS_IB_WC_MAX, wcs)) > 0) {
		for (i = 0; i < nr; i++) {
			wc = wcs + i;
			rdsdebug("wc wr_id 0x%llx status %u byte_len %u imm_data %u\n",
				 (unsigned long long)wc->wr_id, wc->status,
				 wc->byte_len, be32_to_cpu(wc->ex.imm_data));

			if (wc->wr_id <= ic->i_send_ring.w_nr ||
			    wc->wr_id == RDS_IB_ACK_WR_ID)
				rds_ib_send_cqe_handler(ic, wc);
			else
				rds_ib_mr_cqe_handler(ic, wc);

		}
	}
}