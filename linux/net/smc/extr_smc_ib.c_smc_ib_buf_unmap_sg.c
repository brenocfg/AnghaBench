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
struct smc_ib_device {int /*<<< orphan*/  ibdev; } ;
struct smc_buf_desc {TYPE_1__* sgt; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_4__ {scalar_t__ dma_address; } ;
struct TYPE_3__ {TYPE_2__* sgl; int /*<<< orphan*/  orig_nents; } ;

/* Variables and functions */
 size_t SMC_SINGLE_LINK ; 
 int /*<<< orphan*/  ib_dma_unmap_sg (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void smc_ib_buf_unmap_sg(struct smc_ib_device *smcibdev,
			 struct smc_buf_desc *buf_slot,
			 enum dma_data_direction data_direction)
{
	if (!buf_slot->sgt[SMC_SINGLE_LINK].sgl->dma_address)
		return; /* already unmapped */

	ib_dma_unmap_sg(smcibdev->ibdev,
			buf_slot->sgt[SMC_SINGLE_LINK].sgl,
			buf_slot->sgt[SMC_SINGLE_LINK].orig_nents,
			data_direction);
	buf_slot->sgt[SMC_SINGLE_LINK].sgl->dma_address = 0;
}