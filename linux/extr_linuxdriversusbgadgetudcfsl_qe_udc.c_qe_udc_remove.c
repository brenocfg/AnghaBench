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
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {TYPE_2__ dev; } ;
struct qe_udc {int /*<<< orphan*/  usb_regs; int /*<<< orphan*/  rx_tasklet; int /*<<< orphan*/  usb_irq; TYPE_3__ gadget; struct qe_ep* eps; void* nullp; scalar_t__ nullmap; int /*<<< orphan*/ * done; } ;
struct TYPE_4__ {int maxpacket; } ;
struct qe_ep {int /*<<< orphan*/  txframe; int /*<<< orphan*/  rxbuffer; void* rxbuf_d; scalar_t__ rxbufmap; int /*<<< orphan*/  rxframe; TYPE_1__ ep; int /*<<< orphan*/  rxbase; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 void* DMA_ADDR_INVALID ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int USB_BDRING_LEN ; 
 int USB_CRC_SIZE ; 
 int /*<<< orphan*/  cpm_muram_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpm_muram_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,void*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct qe_udc*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct qe_udc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_del_gadget_udc (TYPE_3__*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qe_udc_remove(struct platform_device *ofdev)
{
	struct qe_udc *udc = platform_get_drvdata(ofdev);
	struct qe_ep *ep;
	unsigned int size;
	DECLARE_COMPLETION_ONSTACK(done);

	usb_del_gadget_udc(&udc->gadget);

	udc->done = &done;
	tasklet_disable(&udc->rx_tasklet);

	if (udc->nullmap) {
		dma_unmap_single(udc->gadget.dev.parent,
			udc->nullp, 256,
				DMA_TO_DEVICE);
			udc->nullp = DMA_ADDR_INVALID;
	} else {
		dma_sync_single_for_cpu(udc->gadget.dev.parent,
			udc->nullp, 256,
				DMA_TO_DEVICE);
	}

	ep = &udc->eps[0];
	cpm_muram_free(cpm_muram_offset(ep->rxbase));
	size = (ep->ep.maxpacket + USB_CRC_SIZE + 2) * (USB_BDRING_LEN + 1);

	kfree(ep->rxframe);
	if (ep->rxbufmap) {
		dma_unmap_single(udc->gadget.dev.parent,
				ep->rxbuf_d, size,
				DMA_FROM_DEVICE);
		ep->rxbuf_d = DMA_ADDR_INVALID;
	} else {
		dma_sync_single_for_cpu(udc->gadget.dev.parent,
				ep->rxbuf_d, size,
				DMA_FROM_DEVICE);
	}

	kfree(ep->rxbuffer);
	kfree(ep->txframe);

	free_irq(udc->usb_irq, udc);
	irq_dispose_mapping(udc->usb_irq);

	tasklet_kill(&udc->rx_tasklet);

	iounmap(udc->usb_regs);

	/* wait for release() of gadget.dev to free udc */
	wait_for_completion(&done);

	return 0;
}