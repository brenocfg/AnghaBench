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
struct TYPE_4__ {int /*<<< orphan*/  ringupd_dmahandle; scalar_t__ ringupd; int /*<<< orphan*/  scratch_dmahandle; scalar_t__ scratch; } ;
struct brcmf_pciedev_info {TYPE_2__ shared; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_DMA_D2H_RINGUPD_BUF_LEN ; 
 int /*<<< orphan*/  BRCMF_DMA_D2H_SCRATCH_BUF_LEN ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
brcmf_pcie_release_scratchbuffers(struct brcmf_pciedev_info *devinfo)
{
	if (devinfo->shared.scratch)
		dma_free_coherent(&devinfo->pdev->dev,
				  BRCMF_DMA_D2H_SCRATCH_BUF_LEN,
				  devinfo->shared.scratch,
				  devinfo->shared.scratch_dmahandle);
	if (devinfo->shared.ringupd)
		dma_free_coherent(&devinfo->pdev->dev,
				  BRCMF_DMA_D2H_RINGUPD_BUF_LEN,
				  devinfo->shared.ringupd,
				  devinfo->shared.ringupd_dmahandle);
}