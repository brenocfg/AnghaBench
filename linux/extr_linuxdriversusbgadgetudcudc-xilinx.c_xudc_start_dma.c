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
typedef  int u32 ;
struct xusb_udc {int (* read_fn ) (scalar_t__) ;int /*<<< orphan*/  dev; scalar_t__ addr; int /*<<< orphan*/  (* write_fn ) (scalar_t__,int /*<<< orphan*/ ,int) ;} ;
struct xusb_ep {struct xusb_udc* udc; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  XUSB_DMA_DDAR_ADDR_OFFSET ; 
 int XUSB_DMA_DMASR_BUSY ; 
 int XUSB_DMA_DMASR_ERROR ; 
 int /*<<< orphan*/  XUSB_DMA_DSAR_ADDR_OFFSET ; 
 int /*<<< orphan*/  XUSB_DMA_LENGTH_OFFSET ; 
 scalar_t__ XUSB_DMA_STATUS_OFFSET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int stub4 (scalar_t__) ; 
 int stub5 (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int xudc_start_dma(struct xusb_ep *ep, dma_addr_t src,
			  dma_addr_t dst, u32 length)
{
	struct xusb_udc *udc = ep->udc;
	int rc = 0;
	u32 timeout = 500;
	u32 reg;

	/*
	 * Set the addresses in the DMA source and
	 * destination registers and then set the length
	 * into the DMA length register.
	 */
	udc->write_fn(udc->addr, XUSB_DMA_DSAR_ADDR_OFFSET, src);
	udc->write_fn(udc->addr, XUSB_DMA_DDAR_ADDR_OFFSET, dst);
	udc->write_fn(udc->addr, XUSB_DMA_LENGTH_OFFSET, length);

	/*
	 * Wait till DMA transaction is complete and
	 * check whether the DMA transaction was
	 * successful.
	 */
	do {
		reg = udc->read_fn(udc->addr + XUSB_DMA_STATUS_OFFSET);
		if (!(reg &  XUSB_DMA_DMASR_BUSY))
			break;

		/*
		 * We can't sleep here, because it's also called from
		 * interrupt context.
		 */
		timeout--;
		if (!timeout) {
			dev_err(udc->dev, "DMA timeout\n");
			return -ETIMEDOUT;
		}
		udelay(1);
	} while (1);

	if ((udc->read_fn(udc->addr + XUSB_DMA_STATUS_OFFSET) &
			  XUSB_DMA_DMASR_ERROR) == XUSB_DMA_DMASR_ERROR){
		dev_err(udc->dev, "DMA Error\n");
		rc = -EINVAL;
	}

	return rc;
}