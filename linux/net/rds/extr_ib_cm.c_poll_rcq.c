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
struct rds_ib_connection {int dummy; } ;
struct rds_ib_ack_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  imm_data; } ;
struct ib_wc {TYPE_1__ ex; int /*<<< orphan*/  byte_len; int /*<<< orphan*/  status; scalar_t__ wr_id; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_IB_WC_MAX ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int ib_poll_cq (struct ib_cq*,int /*<<< orphan*/ ,struct ib_wc*) ; 
 int /*<<< orphan*/  rds_ib_recv_cqe_handler (struct rds_ib_connection*,struct ib_wc*,struct rds_ib_ack_state*) ; 
 int /*<<< orphan*/  rdsdebug (char*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void poll_rcq(struct rds_ib_connection *ic, struct ib_cq *cq,
		     struct ib_wc *wcs,
		     struct rds_ib_ack_state *ack_state)
{
	int nr, i;
	struct ib_wc *wc;

	while ((nr = ib_poll_cq(cq, RDS_IB_WC_MAX, wcs)) > 0) {
		for (i = 0; i < nr; i++) {
			wc = wcs + i;
			rdsdebug("wc wr_id 0x%llx status %u byte_len %u imm_data %u\n",
				 (unsigned long long)wc->wr_id, wc->status,
				 wc->byte_len, be32_to_cpu(wc->ex.imm_data));

			rds_ib_recv_cqe_handler(ic, wc, ack_state);
		}
	}
}