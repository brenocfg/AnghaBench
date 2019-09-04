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
typedef  int /*<<< orphan*/  wc ;
struct smc_ib_device {int /*<<< orphan*/  roce_cq_recv; } ;
struct ib_wc {int dummy; } ;

/* Variables and functions */
 int IB_CQ_REPORT_MISSED_EVENTS ; 
 int IB_CQ_SOLICITED_MASK ; 
 int SMC_WR_MAX_POLL_CQE ; 
 int ib_poll_cq (int /*<<< orphan*/ ,int,struct ib_wc*) ; 
 int /*<<< orphan*/  ib_req_notify_cq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ib_wc**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smc_wr_rx_process_cqes (struct ib_wc*,int) ; 

__attribute__((used)) static void smc_wr_rx_tasklet_fn(unsigned long data)
{
	struct smc_ib_device *dev = (struct smc_ib_device *)data;
	struct ib_wc wc[SMC_WR_MAX_POLL_CQE];
	int polled = 0;
	int rc;

again:
	polled++;
	do {
		memset(&wc, 0, sizeof(wc));
		rc = ib_poll_cq(dev->roce_cq_recv, SMC_WR_MAX_POLL_CQE, wc);
		if (polled == 1) {
			ib_req_notify_cq(dev->roce_cq_recv,
					 IB_CQ_SOLICITED_MASK
					 | IB_CQ_REPORT_MISSED_EVENTS);
		}
		if (!rc)
			break;
		smc_wr_rx_process_cqes(&wc[0], rc);
	} while (rc > 0);
	if (polled == 1)
		goto again;
}