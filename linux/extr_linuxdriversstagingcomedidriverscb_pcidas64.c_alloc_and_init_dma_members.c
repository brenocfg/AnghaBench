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
struct plx_dma_desc {int dummy; } ;
struct pcidas64_private {int* ai_buffer_bus_addr; int* ao_buffer_bus_addr; int ai_dma_desc_bus_addr; int ao_dma_desc_bus_addr; int local1_iobase; int local0_iobase; TYPE_2__* ao_dma_desc; TYPE_1__* ai_dma_desc; void** ao_buffer; void** ai_buffer; } ;
struct pcidas64_board {scalar_t__ layout; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct comedi_device {struct pcidas64_private* private; struct pcidas64_board* board_ptr; } ;
struct TYPE_4__ {void* next; void* transfer_size; void* local_start_addr; void* pci_start_addr; } ;
struct TYPE_3__ {void* next; void* transfer_size; void* local_start_addr; void* pci_start_addr; } ;

/* Variables and functions */
 int ADC_FIFO_REG ; 
 int AO_DMA_RING_COUNT ; 
 int DAC_FIFO_REG ; 
 int DMA_BUFFER_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ LAYOUT_4020 ; 
 int PLX_DMADPR_DESCPCI ; 
 int PLX_DMADPR_TCINTR ; 
 int PLX_DMADPR_XFERL2P ; 
 int ai_dma_ring_count (struct pcidas64_board const*) ; 
 scalar_t__ ao_cmd_is_supported (struct pcidas64_board const*) ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 void* cpu_to_le32 (int) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_and_init_dma_members(struct comedi_device *dev)
{
	const struct pcidas64_board *board = dev->board_ptr;
	struct pci_dev *pcidev = comedi_to_pci_dev(dev);
	struct pcidas64_private *devpriv = dev->private;
	int i;

	/* allocate pci dma buffers */
	for (i = 0; i < ai_dma_ring_count(board); i++) {
		devpriv->ai_buffer[i] =
			dma_alloc_coherent(&pcidev->dev, DMA_BUFFER_SIZE,
					   &devpriv->ai_buffer_bus_addr[i],
					   GFP_KERNEL);
		if (!devpriv->ai_buffer[i])
			return -ENOMEM;
	}
	for (i = 0; i < AO_DMA_RING_COUNT; i++) {
		if (ao_cmd_is_supported(board)) {
			devpriv->ao_buffer[i] =
			    dma_alloc_coherent(&pcidev->dev,
					       DMA_BUFFER_SIZE,
					       &devpriv->ao_buffer_bus_addr[i],
					       GFP_KERNEL);
			if (!devpriv->ao_buffer[i])
				return -ENOMEM;
		}
	}
	/* allocate dma descriptors */
	devpriv->ai_dma_desc =
		dma_alloc_coherent(&pcidev->dev, sizeof(struct plx_dma_desc) *
				   ai_dma_ring_count(board),
				   &devpriv->ai_dma_desc_bus_addr, GFP_KERNEL);
	if (!devpriv->ai_dma_desc)
		return -ENOMEM;

	if (ao_cmd_is_supported(board)) {
		devpriv->ao_dma_desc =
			dma_alloc_coherent(&pcidev->dev,
					   sizeof(struct plx_dma_desc) *
					   AO_DMA_RING_COUNT,
					   &devpriv->ao_dma_desc_bus_addr,
					   GFP_KERNEL);
		if (!devpriv->ao_dma_desc)
			return -ENOMEM;
	}
	/* initialize dma descriptors */
	for (i = 0; i < ai_dma_ring_count(board); i++) {
		devpriv->ai_dma_desc[i].pci_start_addr =
			cpu_to_le32(devpriv->ai_buffer_bus_addr[i]);
		if (board->layout == LAYOUT_4020)
			devpriv->ai_dma_desc[i].local_start_addr =
				cpu_to_le32(devpriv->local1_iobase +
					    ADC_FIFO_REG);
		else
			devpriv->ai_dma_desc[i].local_start_addr =
				cpu_to_le32(devpriv->local0_iobase +
					    ADC_FIFO_REG);
		devpriv->ai_dma_desc[i].transfer_size = cpu_to_le32(0);
		devpriv->ai_dma_desc[i].next =
			cpu_to_le32((devpriv->ai_dma_desc_bus_addr +
				     ((i + 1) % ai_dma_ring_count(board)) *
				     sizeof(devpriv->ai_dma_desc[0])) |
				    PLX_DMADPR_DESCPCI | PLX_DMADPR_TCINTR |
				    PLX_DMADPR_XFERL2P);
	}
	if (ao_cmd_is_supported(board)) {
		for (i = 0; i < AO_DMA_RING_COUNT; i++) {
			devpriv->ao_dma_desc[i].pci_start_addr =
				cpu_to_le32(devpriv->ao_buffer_bus_addr[i]);
			devpriv->ao_dma_desc[i].local_start_addr =
				cpu_to_le32(devpriv->local0_iobase +
					    DAC_FIFO_REG);
			devpriv->ao_dma_desc[i].transfer_size = cpu_to_le32(0);
			devpriv->ao_dma_desc[i].next =
				cpu_to_le32((devpriv->ao_dma_desc_bus_addr +
					     ((i + 1) % (AO_DMA_RING_COUNT)) *
					     sizeof(devpriv->ao_dma_desc[0])) |
					    PLX_DMADPR_DESCPCI |
					    PLX_DMADPR_TCINTR);
		}
	}
	return 0;
}