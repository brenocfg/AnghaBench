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
struct comedi_device {int /*<<< orphan*/  hw_dev; struct apci3120_private* private; } ;
struct apci3120_private {int use_dma; int use_double_buffer; struct apci3120_dmabuf* dmabuf; } ;
struct apci3120_dmabuf {int size; scalar_t__ virt; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apci3120_dma_alloc(struct comedi_device *dev)
{
	struct apci3120_private *devpriv = dev->private;
	struct apci3120_dmabuf *dmabuf;
	int order;
	int i;

	for (i = 0; i < 2; i++) {
		dmabuf = &devpriv->dmabuf[i];
		for (order = 2; order >= 0; order--) {
			dmabuf->virt = dma_alloc_coherent(dev->hw_dev,
							  PAGE_SIZE << order,
							  &dmabuf->hw,
							  GFP_KERNEL);
			if (dmabuf->virt)
				break;
		}
		if (!dmabuf->virt)
			break;
		dmabuf->size = PAGE_SIZE << order;

		if (i == 0)
			devpriv->use_dma = 1;
		if (i == 1)
			devpriv->use_double_buffer = 1;
	}
}