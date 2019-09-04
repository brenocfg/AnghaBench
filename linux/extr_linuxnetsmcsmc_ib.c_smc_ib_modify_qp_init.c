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
struct smc_link {int /*<<< orphan*/  roce_qp; int /*<<< orphan*/  ibport; } ;
struct ib_qp_attr {int qp_access_flags; int /*<<< orphan*/  port_num; scalar_t__ pkey_index; int /*<<< orphan*/  qp_state; } ;
typedef  int /*<<< orphan*/  qp_attr ;

/* Variables and functions */
 int IB_ACCESS_LOCAL_WRITE ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int /*<<< orphan*/  IB_QPS_INIT ; 
 int IB_QP_ACCESS_FLAGS ; 
 int IB_QP_PKEY_INDEX ; 
 int IB_QP_PORT ; 
 int IB_QP_STATE ; 
 int ib_modify_qp (int /*<<< orphan*/ ,struct ib_qp_attr*,int) ; 
 int /*<<< orphan*/  memset (struct ib_qp_attr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int smc_ib_modify_qp_init(struct smc_link *lnk)
{
	struct ib_qp_attr qp_attr;

	memset(&qp_attr, 0, sizeof(qp_attr));
	qp_attr.qp_state = IB_QPS_INIT;
	qp_attr.pkey_index = 0;
	qp_attr.port_num = lnk->ibport;
	qp_attr.qp_access_flags = IB_ACCESS_LOCAL_WRITE
				| IB_ACCESS_REMOTE_WRITE;
	return ib_modify_qp(lnk->roce_qp, &qp_attr,
			    IB_QP_STATE | IB_QP_PKEY_INDEX |
			    IB_QP_ACCESS_FLAGS | IB_QP_PORT);
}