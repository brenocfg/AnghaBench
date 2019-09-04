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
struct urb {scalar_t__ transfer_buffer_length; int /*<<< orphan*/  transfer_flags; scalar_t__ transfer_buffer; scalar_t__ sg; scalar_t__ num_sgs; } ;
struct dma_aligned_buffer {scalar_t__ data; scalar_t__ old_xfer_buffer; struct dma_aligned_buffer* kmalloc_ptr; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct dma_aligned_buffer* PTR_ALIGN (struct dma_aligned_buffer*,int) ; 
 int TEGRA_USB_DMA_ALIGN ; 
 int /*<<< orphan*/  URB_ALIGNED_TEMP_BUFFER ; 
 struct dma_aligned_buffer* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 scalar_t__ usb_urb_dir_out (struct urb*) ; 

__attribute__((used)) static int alloc_dma_aligned_buffer(struct urb *urb, gfp_t mem_flags)
{
	struct dma_aligned_buffer *temp, *kmalloc_ptr;
	size_t kmalloc_size;

	if (urb->num_sgs || urb->sg ||
	    urb->transfer_buffer_length == 0 ||
	    !((uintptr_t)urb->transfer_buffer & (TEGRA_USB_DMA_ALIGN - 1)))
		return 0;

	/* Allocate a buffer with enough padding for alignment */
	kmalloc_size = urb->transfer_buffer_length +
		sizeof(struct dma_aligned_buffer) + TEGRA_USB_DMA_ALIGN - 1;

	kmalloc_ptr = kmalloc(kmalloc_size, mem_flags);
	if (!kmalloc_ptr)
		return -ENOMEM;

	/* Position our struct dma_aligned_buffer such that data is aligned */
	temp = PTR_ALIGN(kmalloc_ptr + 1, TEGRA_USB_DMA_ALIGN) - 1;
	temp->kmalloc_ptr = kmalloc_ptr;
	temp->old_xfer_buffer = urb->transfer_buffer;
	if (usb_urb_dir_out(urb))
		memcpy(temp->data, urb->transfer_buffer,
		       urb->transfer_buffer_length);
	urb->transfer_buffer = temp->data;

	urb->transfer_flags |= URB_ALIGNED_TEMP_BUFFER;

	return 0;
}