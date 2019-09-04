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
typedef  int /*<<< orphan*/  usb_complete_t ;
typedef  int /*<<< orphan*/  u8 ;
struct usb_device {scalar_t__ speed; } ;
struct urb {int interval; unsigned int transfer_flags; unsigned int transfer_buffer; int pipe; int /*<<< orphan*/  transfer_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GUARD_BYTE ; 
 int INTERRUPT_RATE ; 
 int URB_NO_TRANSFER_DMA_MAP ; 
 unsigned int URB_SHORT_NOT_OK ; 
 scalar_t__ USB_SPEED_HIGH ; 
 unsigned int kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned int,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned int usb_alloc_coherent (struct usb_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (struct urb*,struct usb_device*,int,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_fill_int_urb (struct urb*,struct usb_device*,int,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 scalar_t__ usb_pipein (int) ; 

__attribute__((used)) static struct urb *usbtest_alloc_urb(
	struct usb_device	*udev,
	int			pipe,
	unsigned long		bytes,
	unsigned		transfer_flags,
	unsigned		offset,
	u8			bInterval,
	usb_complete_t		complete_fn)
{
	struct urb		*urb;

	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb)
		return urb;

	if (bInterval)
		usb_fill_int_urb(urb, udev, pipe, NULL, bytes, complete_fn,
				NULL, bInterval);
	else
		usb_fill_bulk_urb(urb, udev, pipe, NULL, bytes, complete_fn,
				NULL);

	urb->interval = (udev->speed == USB_SPEED_HIGH)
			? (INTERRUPT_RATE << 3)
			: INTERRUPT_RATE;
	urb->transfer_flags = transfer_flags;
	if (usb_pipein(pipe))
		urb->transfer_flags |= URB_SHORT_NOT_OK;

	if ((bytes + offset) == 0)
		return urb;

	if (urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP)
		urb->transfer_buffer = usb_alloc_coherent(udev, bytes + offset,
			GFP_KERNEL, &urb->transfer_dma);
	else
		urb->transfer_buffer = kmalloc(bytes + offset, GFP_KERNEL);

	if (!urb->transfer_buffer) {
		usb_free_urb(urb);
		return NULL;
	}

	/* To test unaligned transfers add an offset and fill the
		unused memory with a guard value */
	if (offset) {
		memset(urb->transfer_buffer, GUARD_BYTE, offset);
		urb->transfer_buffer += offset;
		if (urb->transfer_flags & URB_NO_TRANSFER_DMA_MAP)
			urb->transfer_dma += offset;
	}

	/* For inbound transfers use guard byte so that test fails if
		data not correctly copied */
	memset(urb->transfer_buffer,
			usb_pipein(urb->pipe) ? GUARD_BYTE : 0,
			bytes);
	return urb;
}