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
struct smc_link {int /*<<< orphan*/  roce_qp; } ;
struct ib_qp_attr {int /*<<< orphan*/  qp_state; } ;
typedef  int /*<<< orphan*/  qp_attr ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPS_RESET ; 
 int /*<<< orphan*/  IB_QP_STATE ; 
 int ib_modify_qp (int /*<<< orphan*/ ,struct ib_qp_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ib_qp_attr*,int /*<<< orphan*/ ,int) ; 

int smc_ib_modify_qp_reset(struct smc_link *lnk)
{
	struct ib_qp_attr qp_attr;

	memset(&qp_attr, 0, sizeof(qp_attr));
	qp_attr.qp_state = IB_QPS_RESET;
	return ib_modify_qp(lnk->roce_qp, &qp_attr, IB_QP_STATE);
}