#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int pktsts; int bcnt; int chnum; } ;
union cvmx_usbcx_grxstsph {TYPE_1__ s; void* u32; } ;
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct octeon_hcd {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SYNCW ; 
 int /*<<< orphan*/  CVMX_USBCX_GRXSTSPH (int /*<<< orphan*/ ) ; 
 scalar_t__ CVMX_USBNX_DMA0_INB_CHN0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_FIFO_ADDRESS (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cvmx_phys_to_ptr (scalar_t__) ; 
 scalar_t__ cvmx_read64_uint64 (scalar_t__) ; 
 void* cvmx_usb_read_csr32 (struct octeon_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write64_uint64 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void cvmx_usb_poll_rx_fifo(struct octeon_hcd *usb)
{
	union cvmx_usbcx_grxstsph rx_status;
	int channel;
	int bytes;
	u64 address;
	u32 *ptr;

	rx_status.u32 = cvmx_usb_read_csr32(usb,
					    CVMX_USBCX_GRXSTSPH(usb->index));
	/* Only read data if IN data is there */
	if (rx_status.s.pktsts != 2)
		return;
	/* Check if no data is available */
	if (!rx_status.s.bcnt)
		return;

	channel = rx_status.s.chnum;
	bytes = rx_status.s.bcnt;
	if (!bytes)
		return;

	/* Get where the DMA engine would have written this data */
	address = cvmx_read64_uint64(CVMX_USBNX_DMA0_INB_CHN0(usb->index) +
				     channel * 8);

	ptr = cvmx_phys_to_ptr(address);
	cvmx_write64_uint64(CVMX_USBNX_DMA0_INB_CHN0(usb->index) + channel * 8,
			    address + bytes);

	/* Loop writing the FIFO data for this packet into memory */
	while (bytes > 0) {
		*ptr++ = cvmx_usb_read_csr32(usb,
					USB_FIFO_ADDRESS(channel, usb->index));
		bytes -= 4;
	}
	CVMX_SYNCW;
}