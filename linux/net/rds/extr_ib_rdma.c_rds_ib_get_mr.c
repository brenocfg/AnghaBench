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
typedef  int /*<<< orphan*/  u32 ;
struct scatterlist {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * s6_addr32; } ;
struct rds_sock {TYPE_1__ rs_bound_addr; } ;
typedef  void rds_ib_mr ;
struct rds_ib_device {scalar_t__ use_fastreg; int /*<<< orphan*/  mr_1m_pool; int /*<<< orphan*/  mr_8k_pool; } ;
struct rds_ib_connection {int dummy; } ;
struct rds_connection {struct rds_ib_connection* c_transport_data; } ;

/* Variables and functions */
 int ENODEV ; 
 void* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  rds_ib_dev_put (struct rds_ib_device*) ; 
 struct rds_ib_device* rds_ib_get_device (int /*<<< orphan*/ ) ; 
 void* rds_ib_reg_fmr (struct rds_ib_device*,struct scatterlist*,unsigned long,int /*<<< orphan*/ *) ; 
 void* rds_ib_reg_frmr (struct rds_ib_device*,struct rds_ib_connection*,struct scatterlist*,unsigned long,int /*<<< orphan*/ *) ; 

void *rds_ib_get_mr(struct scatterlist *sg, unsigned long nents,
		    struct rds_sock *rs, u32 *key_ret,
		    struct rds_connection *conn)
{
	struct rds_ib_device *rds_ibdev;
	struct rds_ib_mr *ibmr = NULL;
	struct rds_ib_connection *ic = NULL;
	int ret;

	rds_ibdev = rds_ib_get_device(rs->rs_bound_addr.s6_addr32[3]);
	if (!rds_ibdev) {
		ret = -ENODEV;
		goto out;
	}

	if (conn)
		ic = conn->c_transport_data;

	if (!rds_ibdev->mr_8k_pool || !rds_ibdev->mr_1m_pool) {
		ret = -ENODEV;
		goto out;
	}

	if (rds_ibdev->use_fastreg)
		ibmr = rds_ib_reg_frmr(rds_ibdev, ic, sg, nents, key_ret);
	else
		ibmr = rds_ib_reg_fmr(rds_ibdev, sg, nents, key_ret);
	if (IS_ERR(ibmr)) {
		ret = PTR_ERR(ibmr);
		pr_warn("RDS/IB: rds_ib_get_mr failed (errno=%d)\n", ret);
	} else {
		return ibmr;
	}

 out:
	if (rds_ibdev)
		rds_ib_dev_put(rds_ibdev);

	return ERR_PTR(ret);
}