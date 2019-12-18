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
struct smc_link_group {TYPE_1__* lnk; scalar_t__ is_smcd; } ;
struct smc_connection {int /*<<< orphan*/  rmb_desc; struct smc_link_group* lgr; } ;
struct TYPE_2__ {int /*<<< orphan*/  smcibdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 size_t SMC_SINGLE_LINK ; 
 int /*<<< orphan*/  smc_ib_sync_sg_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void smc_rmb_sync_sg_for_device(struct smc_connection *conn)
{
	struct smc_link_group *lgr = conn->lgr;

	if (!conn->lgr || conn->lgr->is_smcd)
		return;
	smc_ib_sync_sg_for_device(lgr->lnk[SMC_SINGLE_LINK].smcibdev,
				  conn->rmb_desc, DMA_FROM_DEVICE);
}