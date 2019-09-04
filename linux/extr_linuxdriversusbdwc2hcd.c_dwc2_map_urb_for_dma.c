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
struct usb_hcd {int dummy; } ;
struct urb {int setup_dma; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int DWC2_USB_DMA_ALIGN ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int dwc2_alloc_dma_aligned_buffer (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc2_free_dma_aligned_buffer (struct urb*) ; 
 int usb_hcd_map_urb_for_dma (struct usb_hcd*,struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc2_map_urb_for_dma(struct usb_hcd *hcd, struct urb *urb,
				gfp_t mem_flags)
{
	int ret;

	/* We assume setup_dma is always aligned; warn if not */
	WARN_ON_ONCE(urb->setup_dma &&
		     (urb->setup_dma & (DWC2_USB_DMA_ALIGN - 1)));

	ret = dwc2_alloc_dma_aligned_buffer(urb, mem_flags);
	if (ret)
		return ret;

	ret = usb_hcd_map_urb_for_dma(hcd, urb, mem_flags);
	if (ret)
		dwc2_free_dma_aligned_buffer(urb);

	return ret;
}