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
struct scatterlist {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void ccio_unmap_sg(struct pci_dev *dev, struct scatterlist *sglist, int nents, int direction)
{
#if 0
	while (nents) {
		ccio_unmap_single(dev, sg_dma_address(sglist), sg_dma_len(sglist), direction);
		nents--;
		sglist++;
	}
	return;
#else
	/* Do nothing (copied from current ccio_unmap_single()  :^) */
#endif
}