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
struct TYPE_3__ {int /*<<< orphan*/  sysdev; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct urb {int transfer_flags; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  transfer_buffer; int /*<<< orphan*/  transfer_dma; TYPE_2__* dev; int /*<<< orphan*/  num_sgs; int /*<<< orphan*/  sg; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_4__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_HAS_DMA ; 
 int DMA_FROM_DEVICE ; 
 int DMA_TO_DEVICE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int URB_DMA_MAP_PAGE ; 
 int URB_DMA_MAP_SG ; 
 int URB_DMA_MAP_SINGLE ; 
 int URB_MAP_LOCAL ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hcd_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_hcd_unmap_urb_setup_for_dma (struct usb_hcd*,struct urb*) ; 
 scalar_t__ usb_urb_dir_in (struct urb*) ; 

void usb_hcd_unmap_urb_for_dma(struct usb_hcd *hcd, struct urb *urb)
{
	enum dma_data_direction dir;

	usb_hcd_unmap_urb_setup_for_dma(hcd, urb);

	dir = usb_urb_dir_in(urb) ? DMA_FROM_DEVICE : DMA_TO_DEVICE;
	if (IS_ENABLED(CONFIG_HAS_DMA) &&
	    (urb->transfer_flags & URB_DMA_MAP_SG))
		dma_unmap_sg(hcd->self.sysdev,
				urb->sg,
				urb->num_sgs,
				dir);
	else if (IS_ENABLED(CONFIG_HAS_DMA) &&
		 (urb->transfer_flags & URB_DMA_MAP_PAGE))
		dma_unmap_page(hcd->self.sysdev,
				urb->transfer_dma,
				urb->transfer_buffer_length,
				dir);
	else if (IS_ENABLED(CONFIG_HAS_DMA) &&
		 (urb->transfer_flags & URB_DMA_MAP_SINGLE))
		dma_unmap_single(hcd->self.sysdev,
				urb->transfer_dma,
				urb->transfer_buffer_length,
				dir);
	else if (urb->transfer_flags & URB_MAP_LOCAL)
		hcd_free_coherent(urb->dev->bus,
				&urb->transfer_dma,
				&urb->transfer_buffer,
				urb->transfer_buffer_length,
				dir);

	/* Make it safe to call this routine more than once */
	urb->transfer_flags &= ~(URB_DMA_MAP_SG | URB_DMA_MAP_PAGE |
			URB_DMA_MAP_SINGLE | URB_MAP_LOCAL);
}