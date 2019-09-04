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
struct plx_dma_desc {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hpdi_private {int /*<<< orphan*/  dma_desc_phys_addr; scalar_t__ dma_desc; int /*<<< orphan*/ * dio_buffer_phys_addr; scalar_t__* dio_buffer; } ;
struct comedi_device {struct hpdi_private* private; } ;

/* Variables and functions */
 int DMA_BUFFER_SIZE ; 
 int NUM_DMA_BUFFERS ; 
 int NUM_DMA_DESCRIPTORS ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gsc_hpdi_free_dma(struct comedi_device *dev)
{
	struct pci_dev *pcidev = comedi_to_pci_dev(dev);
	struct hpdi_private *devpriv = dev->private;
	int i;

	if (!devpriv)
		return;

	/* free pci dma buffers */
	for (i = 0; i < NUM_DMA_BUFFERS; i++) {
		if (devpriv->dio_buffer[i])
			dma_free_coherent(&pcidev->dev,
					  DMA_BUFFER_SIZE,
					  devpriv->dio_buffer[i],
					  devpriv->dio_buffer_phys_addr[i]);
	}
	/* free dma descriptors */
	if (devpriv->dma_desc)
		dma_free_coherent(&pcidev->dev,
				  sizeof(struct plx_dma_desc) *
				  NUM_DMA_DESCRIPTORS,
				  devpriv->dma_desc,
				  devpriv->dma_desc_phys_addr);
}