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
struct smc_buf_desc {int order; int /*<<< orphan*/ ** mr_rx; } ;
struct ib_pd {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IB_MR_TYPE_MEM_REG ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 size_t SMC_SINGLE_LINK ; 
 int /*<<< orphan*/ * ib_alloc_mr (struct ib_pd*,int /*<<< orphan*/ ,int) ; 
 int smc_ib_map_mr_sg (struct smc_buf_desc*) ; 

int smc_ib_get_memory_region(struct ib_pd *pd, int access_flags,
			     struct smc_buf_desc *buf_slot)
{
	if (buf_slot->mr_rx[SMC_SINGLE_LINK])
		return 0; /* already done */

	buf_slot->mr_rx[SMC_SINGLE_LINK] =
		ib_alloc_mr(pd, IB_MR_TYPE_MEM_REG, 1 << buf_slot->order);
	if (IS_ERR(buf_slot->mr_rx[SMC_SINGLE_LINK])) {
		int rc;

		rc = PTR_ERR(buf_slot->mr_rx[SMC_SINGLE_LINK]);
		buf_slot->mr_rx[SMC_SINGLE_LINK] = NULL;
		return rc;
	}

	if (smc_ib_map_mr_sg(buf_slot) != 1)
		return -EINVAL;

	return 0;
}