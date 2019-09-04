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
struct smc_ib_device {int /*<<< orphan*/  roce_cq_send; int /*<<< orphan*/  roce_cq_recv; scalar_t__ initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_destroy_cq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_wr_remove_dev (struct smc_ib_device*) ; 

__attribute__((used)) static void smc_ib_cleanup_per_ibdev(struct smc_ib_device *smcibdev)
{
	if (!smcibdev->initialized)
		return;
	smcibdev->initialized = 0;
	smc_wr_remove_dev(smcibdev);
	ib_destroy_cq(smcibdev->roce_cq_recv);
	ib_destroy_cq(smcibdev->roce_cq_send);
}