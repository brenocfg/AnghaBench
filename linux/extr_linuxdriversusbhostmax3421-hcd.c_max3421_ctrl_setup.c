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
struct urb {int /*<<< orphan*/  setup_packet; } ;

/* Variables and functions */
 int MAX3421_HXFR_SETUP ; 
 int /*<<< orphan*/  MAX3421_REG_SUDFIFO ; 
 int /*<<< orphan*/  spi_wr_buf (struct usb_hcd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
max3421_ctrl_setup(struct usb_hcd *hcd, struct urb *urb)
{
	spi_wr_buf(hcd, MAX3421_REG_SUDFIFO, urb->setup_packet, 8);
	return MAX3421_HXFR_SETUP;
}