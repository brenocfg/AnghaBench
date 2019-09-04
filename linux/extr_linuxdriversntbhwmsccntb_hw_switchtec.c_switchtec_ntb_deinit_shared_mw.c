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
struct switchtec_ntb {int /*<<< orphan*/  nr_rsvd_luts; int /*<<< orphan*/  self_shared_dma; scalar_t__ self_shared; TYPE_1__* stdev; scalar_t__ peer_shared; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {TYPE_2__* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUT_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static void switchtec_ntb_deinit_shared_mw(struct switchtec_ntb *sndev)
{
	if (sndev->peer_shared)
		pci_iounmap(sndev->stdev->pdev, sndev->peer_shared);

	if (sndev->self_shared)
		dma_free_coherent(&sndev->stdev->pdev->dev, LUT_SIZE,
				  sndev->self_shared,
				  sndev->self_shared_dma);
	sndev->nr_rsvd_luts--;
}