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
struct smc_ib_device {int /*<<< orphan*/  ibdev; } ;
struct smc_buf_desc {TYPE_1__* sgt; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_2__ {int /*<<< orphan*/  orig_nents; int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t SMC_SINGLE_LINK ; 
 int ib_dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int smc_ib_buf_map_sg(struct smc_ib_device *smcibdev,
		      struct smc_buf_desc *buf_slot,
		      enum dma_data_direction data_direction)
{
	int mapped_nents;

	mapped_nents = ib_dma_map_sg(smcibdev->ibdev,
				     buf_slot->sgt[SMC_SINGLE_LINK].sgl,
				     buf_slot->sgt[SMC_SINGLE_LINK].orig_nents,
				     data_direction);
	if (!mapped_nents)
		return -ENOMEM;

	return mapped_nents;
}