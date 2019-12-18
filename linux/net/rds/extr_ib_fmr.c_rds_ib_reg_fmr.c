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
typedef  int /*<<< orphan*/  u32 ;
struct scatterlist {int dummy; } ;
struct rds_ib_fmr {TYPE_1__* fmr; } ;
struct TYPE_4__ {struct rds_ib_fmr fmr; } ;
struct rds_ib_mr {TYPE_2__ u; struct rds_ib_device* device; } ;
struct rds_ib_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rkey; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct rds_ib_mr*) ; 
 struct rds_ib_mr* rds_ib_alloc_fmr (struct rds_ib_device*,unsigned long) ; 
 int /*<<< orphan*/  rds_ib_free_mr (struct rds_ib_mr*,int /*<<< orphan*/ ) ; 
 int rds_ib_map_fmr (struct rds_ib_device*,struct rds_ib_mr*,struct scatterlist*,unsigned long) ; 

struct rds_ib_mr *rds_ib_reg_fmr(struct rds_ib_device *rds_ibdev,
				 struct scatterlist *sg,
				 unsigned long nents,
				 u32 *key)
{
	struct rds_ib_mr *ibmr = NULL;
	struct rds_ib_fmr *fmr;
	int ret;

	ibmr = rds_ib_alloc_fmr(rds_ibdev, nents);
	if (IS_ERR(ibmr))
		return ibmr;

	ibmr->device = rds_ibdev;
	fmr = &ibmr->u.fmr;
	ret = rds_ib_map_fmr(rds_ibdev, ibmr, sg, nents);
	if (ret == 0)
		*key = fmr->fmr->rkey;
	else
		rds_ib_free_mr(ibmr, 0);

	return ibmr;
}