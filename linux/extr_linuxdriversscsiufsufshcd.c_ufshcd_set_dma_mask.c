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
struct ufs_hba {int capabilities; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int MASK_64_ADDRESSING_SUPPORT ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ufshcd_set_dma_mask(struct ufs_hba *hba)
{
	if (hba->capabilities & MASK_64_ADDRESSING_SUPPORT) {
		if (!dma_set_mask_and_coherent(hba->dev, DMA_BIT_MASK(64)))
			return 0;
	}
	return dma_set_mask_and_coherent(hba->dev, DMA_BIT_MASK(32));
}