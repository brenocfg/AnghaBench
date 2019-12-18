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
struct smc_link {int /*<<< orphan*/ * roce_pd; TYPE_1__* smcibdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  ibdev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ib_alloc_pd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int smc_ib_create_protection_domain(struct smc_link *lnk)
{
	int rc;

	lnk->roce_pd = ib_alloc_pd(lnk->smcibdev->ibdev, 0);
	rc = PTR_ERR_OR_ZERO(lnk->roce_pd);
	if (IS_ERR(lnk->roce_pd))
		lnk->roce_pd = NULL;
	return rc;
}