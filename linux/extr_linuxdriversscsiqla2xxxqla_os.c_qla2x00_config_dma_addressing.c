#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int enable_64bit_addressing; } ;
struct qla_hw_data {TYPE_3__* pdev; TYPE_1__* isp_ops; TYPE_2__ flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  build_iocbs; int /*<<< orphan*/  calc_req_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 scalar_t__ MSD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_get_required_mask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_set_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_consistent_dma_mask (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_build_scsi_iocbs_64 ; 
 int /*<<< orphan*/  qla2x00_calc_iocbs_64 ; 

__attribute__((used)) static void
qla2x00_config_dma_addressing(struct qla_hw_data *ha)
{
	/* Assume a 32bit DMA mask. */
	ha->flags.enable_64bit_addressing = 0;

	if (!dma_set_mask(&ha->pdev->dev, DMA_BIT_MASK(64))) {
		/* Any upper-dword bits set? */
		if (MSD(dma_get_required_mask(&ha->pdev->dev)) &&
		    !pci_set_consistent_dma_mask(ha->pdev, DMA_BIT_MASK(64))) {
			/* Ok, a 64bit DMA mask is applicable. */
			ha->flags.enable_64bit_addressing = 1;
			ha->isp_ops->calc_req_entries = qla2x00_calc_iocbs_64;
			ha->isp_ops->build_iocbs = qla2x00_build_scsi_iocbs_64;
			return;
		}
	}

	dma_set_mask(&ha->pdev->dev, DMA_BIT_MASK(32));
	pci_set_consistent_dma_mask(ha->pdev, DMA_BIT_MASK(32));
}