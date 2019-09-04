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
struct smc_ib_device {int initialized; int /*<<< orphan*/ * roce_cq_send; int /*<<< orphan*/ * roce_cq_recv; int /*<<< orphan*/  ibdev; } ;
struct ib_cq_init_attr {int cqe; int /*<<< orphan*/  comp_vector; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int MAX_ORDER ; 
 int PAGE_SIZE ; 
 long PTR_ERR_OR_ZERO (int /*<<< orphan*/ *) ; 
 int SMC_MAX_CQE ; 
 int cache_line_size () ; 
 void* ib_create_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct smc_ib_device*,struct ib_cq_init_attr*) ; 
 int /*<<< orphan*/  ib_destroy_cq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_wr_add_dev (struct smc_ib_device*) ; 
 int /*<<< orphan*/  smc_wr_rx_cq_handler ; 
 int /*<<< orphan*/  smc_wr_tx_cq_handler ; 

long smc_ib_setup_per_ibdev(struct smc_ib_device *smcibdev)
{
	struct ib_cq_init_attr cqattr =	{
		.cqe = SMC_MAX_CQE, .comp_vector = 0 };
	int cqe_size_order, smc_order;
	long rc;

	/* the calculated number of cq entries fits to mlx5 cq allocation */
	cqe_size_order = cache_line_size() == 128 ? 7 : 6;
	smc_order = MAX_ORDER - cqe_size_order - 1;
	if (SMC_MAX_CQE + 2 > (0x00000001 << smc_order) * PAGE_SIZE)
		cqattr.cqe = (0x00000001 << smc_order) * PAGE_SIZE - 2;
	smcibdev->roce_cq_send = ib_create_cq(smcibdev->ibdev,
					      smc_wr_tx_cq_handler, NULL,
					      smcibdev, &cqattr);
	rc = PTR_ERR_OR_ZERO(smcibdev->roce_cq_send);
	if (IS_ERR(smcibdev->roce_cq_send)) {
		smcibdev->roce_cq_send = NULL;
		return rc;
	}
	smcibdev->roce_cq_recv = ib_create_cq(smcibdev->ibdev,
					      smc_wr_rx_cq_handler, NULL,
					      smcibdev, &cqattr);
	rc = PTR_ERR_OR_ZERO(smcibdev->roce_cq_recv);
	if (IS_ERR(smcibdev->roce_cq_recv)) {
		smcibdev->roce_cq_recv = NULL;
		goto err;
	}
	smc_wr_add_dev(smcibdev);
	smcibdev->initialized = 1;
	return rc;

err:
	ib_destroy_cq(smcibdev->roce_cq_send);
	return rc;
}