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
struct TYPE_2__ {int enable; int por; int hclk_rst; scalar_t__ hrst; scalar_t__ prst; } ;
union cvmx_usbnx_clk_ctl {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
struct octeon_hcd {int /*<<< orphan*/  index; int /*<<< orphan*/ * active_pipes; int /*<<< orphan*/  idle_pipes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USBNX_CLK_CTL (int /*<<< orphan*/ ) ; 
 size_t CVMX_USB_TRANSFER_BULK ; 
 size_t CVMX_USB_TRANSFER_CONTROL ; 
 size_t CVMX_USB_TRANSFER_INTERRUPT ; 
 size_t CVMX_USB_TRANSFER_ISOCHRONOUS ; 
 int EBUSY ; 
 int /*<<< orphan*/  cvmx_read64_uint64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write64_uint64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cvmx_usb_shutdown(struct octeon_hcd *usb)
{
	union cvmx_usbnx_clk_ctl usbn_clk_ctl;

	/* Make sure all pipes are closed */
	if (!list_empty(&usb->idle_pipes) ||
	    !list_empty(&usb->active_pipes[CVMX_USB_TRANSFER_ISOCHRONOUS]) ||
	    !list_empty(&usb->active_pipes[CVMX_USB_TRANSFER_INTERRUPT]) ||
	    !list_empty(&usb->active_pipes[CVMX_USB_TRANSFER_CONTROL]) ||
	    !list_empty(&usb->active_pipes[CVMX_USB_TRANSFER_BULK]))
		return -EBUSY;

	/* Disable the clocks and put them in power on reset */
	usbn_clk_ctl.u64 = cvmx_read64_uint64(CVMX_USBNX_CLK_CTL(usb->index));
	usbn_clk_ctl.s.enable = 1;
	usbn_clk_ctl.s.por = 1;
	usbn_clk_ctl.s.hclk_rst = 1;
	usbn_clk_ctl.s.prst = 0;
	usbn_clk_ctl.s.hrst = 0;
	cvmx_write64_uint64(CVMX_USBNX_CLK_CTL(usb->index), usbn_clk_ctl.u64);
	return 0;
}