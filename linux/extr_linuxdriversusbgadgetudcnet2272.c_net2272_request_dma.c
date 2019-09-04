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
typedef  int /*<<< orphan*/  u32 ;
struct net2272 {int dma_busy; int dma_eot_polarity; int dma_dack_polarity; int dma_dreq_polarity; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DACK_POLARITY ; 
 int /*<<< orphan*/  DMAREQ ; 
 int DMA_BUFFER_VALID ; 
 int DMA_CONTROL_DACK ; 
 unsigned int DMA_ENDPOINT_SELECT ; 
 int DMA_REQUEST_ENABLE ; 
 int DREQ_POLARITY ; 
 int EBUSY ; 
 int EINVAL ; 
 int EOT_POLARITY ; 
 int /*<<< orphan*/  SCRATCH ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  net2272_read (struct net2272*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net2272_write (struct net2272*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
net2272_request_dma(struct net2272 *dev, unsigned ep, u32 buf,
	unsigned len, unsigned dir)
{
	dev_vdbg(dev->dev, "request_dma ep %d buf %08x len %d dir %d\n",
		ep, buf, len, dir);

	/* The NET2272 only supports a single dma channel */
	if (dev->dma_busy)
		return -EBUSY;
	/*
	 * EP_TRANSFER (used to determine the number of bytes received
	 * in an OUT transfer) is 24 bits wide; don't ask for more than that.
	 */
	if ((dir == 1) && (len > 0x1000000))
		return -EINVAL;

	dev->dma_busy = 1;

	/* initialize platform's dma */
#ifdef CONFIG_USB_PCI
	/* NET2272 addr, buffer addr, length, etc. */
	switch (dev->dev_id) {
	case PCI_DEVICE_ID_RDK1:
		/* Setup PLX 9054 DMA mode */
		writel((1 << LOCAL_BUS_WIDTH) |
			(1 << TA_READY_INPUT_ENABLE) |
			(0 << LOCAL_BURST_ENABLE) |
			(1 << DONE_INTERRUPT_ENABLE) |
			(1 << LOCAL_ADDRESSING_MODE) |
			(1 << DEMAND_MODE) |
			(1 << DMA_EOT_ENABLE) |
			(1 << FAST_SLOW_TERMINATE_MODE_SELECT) |
			(1 << DMA_CHANNEL_INTERRUPT_SELECT),
			dev->rdk1.plx9054_base_addr + DMAMODE0);

		writel(0x100000, dev->rdk1.plx9054_base_addr + DMALADR0);
		writel(buf, dev->rdk1.plx9054_base_addr + DMAPADR0);
		writel(len, dev->rdk1.plx9054_base_addr + DMASIZ0);
		writel((dir << DIRECTION_OF_TRANSFER) |
			(1 << INTERRUPT_AFTER_TERMINAL_COUNT),
			dev->rdk1.plx9054_base_addr + DMADPR0);
		writel((1 << LOCAL_DMA_CHANNEL_0_INTERRUPT_ENABLE) |
			readl(dev->rdk1.plx9054_base_addr + INTCSR),
			dev->rdk1.plx9054_base_addr + INTCSR);

		break;
	}
#endif

	net2272_write(dev, DMAREQ,
		(0 << DMA_BUFFER_VALID) |
		(1 << DMA_REQUEST_ENABLE) |
		(1 << DMA_CONTROL_DACK) |
		(dev->dma_eot_polarity << EOT_POLARITY) |
		(dev->dma_dack_polarity << DACK_POLARITY) |
		(dev->dma_dreq_polarity << DREQ_POLARITY) |
		((ep >> 1) << DMA_ENDPOINT_SELECT));

	(void) net2272_read(dev, SCRATCH);

	return 0;
}