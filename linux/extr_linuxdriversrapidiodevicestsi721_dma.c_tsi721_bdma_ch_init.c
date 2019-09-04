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
typedef  int u64 ;
struct tsi721_dma_sts {int dummy; } ;
struct tsi721_dma_desc {void* next_hi; void* next_lo; void* type_id; } ;
struct TYPE_6__ {TYPE_2__* dev; TYPE_1__* device; } ;
struct tsi721_bdma_chan {int bd_num; int* sts_base; int sts_size; scalar_t__ sts_rdptr; scalar_t__ wr_count_next; scalar_t__ wr_count; scalar_t__ regs; int /*<<< orphan*/  id; TYPE_3__ dchan; void* sts_phys; struct tsi721_dma_desc* bd_base; void* bd_phys; } ;
struct device {int dummy; } ;
typedef  void* dma_addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA ; 
 int DTYPE3 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ TSI721_DMAC_CTL ; 
 int TSI721_DMAC_CTL_INIT ; 
 scalar_t__ TSI721_DMAC_DPTRH ; 
 scalar_t__ TSI721_DMAC_DPTRL ; 
 int TSI721_DMAC_DPTRL_MASK ; 
 scalar_t__ TSI721_DMAC_DSBH ; 
 scalar_t__ TSI721_DMAC_DSBL ; 
 int TSI721_DMAC_DSBL_MASK ; 
 scalar_t__ TSI721_DMAC_DSSZ ; 
 int TSI721_DMAC_DSSZ_SIZE (int) ; 
 scalar_t__ TSI721_DMAC_INT ; 
 int TSI721_DMAC_INT_ALL ; 
 int TSI721_DMA_MINSTSSZ ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,struct tsi721_dma_desc*,void*) ; 
 void* dma_zalloc_coherent (struct device*,int,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tsi721_bdma_ch_init(struct tsi721_bdma_chan *bdma_chan, int bd_num)
{
	struct tsi721_dma_desc *bd_ptr;
	struct device *dev = bdma_chan->dchan.device->dev;
	u64		*sts_ptr;
	dma_addr_t	bd_phys;
	dma_addr_t	sts_phys;
	int		sts_size;
#ifdef CONFIG_PCI_MSI
	struct tsi721_device *priv = to_tsi721(bdma_chan->dchan.device);
#endif

	tsi_debug(DMA, &bdma_chan->dchan.dev->device, "DMAC%d", bdma_chan->id);

	/*
	 * Allocate space for DMA descriptors
	 * (add an extra element for link descriptor)
	 */
	bd_ptr = dma_zalloc_coherent(dev,
				(bd_num + 1) * sizeof(struct tsi721_dma_desc),
				&bd_phys, GFP_ATOMIC);
	if (!bd_ptr)
		return -ENOMEM;

	bdma_chan->bd_num = bd_num;
	bdma_chan->bd_phys = bd_phys;
	bdma_chan->bd_base = bd_ptr;

	tsi_debug(DMA, &bdma_chan->dchan.dev->device,
		  "DMAC%d descriptors @ %p (phys = %pad)",
		  bdma_chan->id, bd_ptr, &bd_phys);

	/* Allocate space for descriptor status FIFO */
	sts_size = ((bd_num + 1) >= TSI721_DMA_MINSTSSZ) ?
					(bd_num + 1) : TSI721_DMA_MINSTSSZ;
	sts_size = roundup_pow_of_two(sts_size);
	sts_ptr = dma_zalloc_coherent(dev,
				     sts_size * sizeof(struct tsi721_dma_sts),
				     &sts_phys, GFP_ATOMIC);
	if (!sts_ptr) {
		/* Free space allocated for DMA descriptors */
		dma_free_coherent(dev,
				  (bd_num + 1) * sizeof(struct tsi721_dma_desc),
				  bd_ptr, bd_phys);
		bdma_chan->bd_base = NULL;
		return -ENOMEM;
	}

	bdma_chan->sts_phys = sts_phys;
	bdma_chan->sts_base = sts_ptr;
	bdma_chan->sts_size = sts_size;

	tsi_debug(DMA, &bdma_chan->dchan.dev->device,
		"DMAC%d desc status FIFO @ %p (phys = %pad) size=0x%x",
		bdma_chan->id, sts_ptr, &sts_phys, sts_size);

	/* Initialize DMA descriptors ring using added link descriptor */
	bd_ptr[bd_num].type_id = cpu_to_le32(DTYPE3 << 29);
	bd_ptr[bd_num].next_lo = cpu_to_le32((u64)bd_phys &
						 TSI721_DMAC_DPTRL_MASK);
	bd_ptr[bd_num].next_hi = cpu_to_le32((u64)bd_phys >> 32);

	/* Setup DMA descriptor pointers */
	iowrite32(((u64)bd_phys >> 32),
		bdma_chan->regs + TSI721_DMAC_DPTRH);
	iowrite32(((u64)bd_phys & TSI721_DMAC_DPTRL_MASK),
		bdma_chan->regs + TSI721_DMAC_DPTRL);

	/* Setup descriptor status FIFO */
	iowrite32(((u64)sts_phys >> 32),
		bdma_chan->regs + TSI721_DMAC_DSBH);
	iowrite32(((u64)sts_phys & TSI721_DMAC_DSBL_MASK),
		bdma_chan->regs + TSI721_DMAC_DSBL);
	iowrite32(TSI721_DMAC_DSSZ_SIZE(sts_size),
		bdma_chan->regs + TSI721_DMAC_DSSZ);

	/* Clear interrupt bits */
	iowrite32(TSI721_DMAC_INT_ALL,
		bdma_chan->regs + TSI721_DMAC_INT);

	ioread32(bdma_chan->regs + TSI721_DMAC_INT);

#ifdef CONFIG_PCI_MSI
	/* Request interrupt service if we are in MSI-X mode */
	if (priv->flags & TSI721_USING_MSIX) {
		int rc, idx;

		idx = TSI721_VECT_DMA0_DONE + bdma_chan->id;

		rc = request_irq(priv->msix[idx].vector, tsi721_bdma_msix, 0,
				 priv->msix[idx].irq_name, (void *)bdma_chan);

		if (rc) {
			tsi_debug(DMA, &bdma_chan->dchan.dev->device,
				  "Unable to get MSI-X for DMAC%d-DONE",
				  bdma_chan->id);
			goto err_out;
		}

		idx = TSI721_VECT_DMA0_INT + bdma_chan->id;

		rc = request_irq(priv->msix[idx].vector, tsi721_bdma_msix, 0,
				priv->msix[idx].irq_name, (void *)bdma_chan);

		if (rc)	{
			tsi_debug(DMA, &bdma_chan->dchan.dev->device,
				  "Unable to get MSI-X for DMAC%d-INT",
				  bdma_chan->id);
			free_irq(
				priv->msix[TSI721_VECT_DMA0_DONE +
					    bdma_chan->id].vector,
				(void *)bdma_chan);
		}

err_out:
		if (rc) {
			/* Free space allocated for DMA descriptors */
			dma_free_coherent(dev,
				(bd_num + 1) * sizeof(struct tsi721_dma_desc),
				bd_ptr, bd_phys);
			bdma_chan->bd_base = NULL;

			/* Free space allocated for status descriptors */
			dma_free_coherent(dev,
				sts_size * sizeof(struct tsi721_dma_sts),
				sts_ptr, sts_phys);
			bdma_chan->sts_base = NULL;

			return -EIO;
		}
	}
#endif /* CONFIG_PCI_MSI */

	/* Toggle DMA channel initialization */
	iowrite32(TSI721_DMAC_CTL_INIT,	bdma_chan->regs + TSI721_DMAC_CTL);
	ioread32(bdma_chan->regs + TSI721_DMAC_CTL);
	bdma_chan->wr_count = bdma_chan->wr_count_next = 0;
	bdma_chan->sts_rdptr = 0;
	udelay(10);

	return 0;
}