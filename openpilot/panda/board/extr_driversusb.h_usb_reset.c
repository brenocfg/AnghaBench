#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int GRXFSIZ; int DIEPTXF0_HNPTXFSIZ; int* DIEPTXF; int GRSTCTL; } ;
struct TYPE_7__ {int DAINT; int DAINTMSK; int DIEPMSK; int DOEPMSK; int /*<<< orphan*/  DCTL; int /*<<< orphan*/  DCFG; } ;
struct TYPE_6__ {int DIEPINT; } ;
struct TYPE_5__ {int DOEPINT; unsigned int DOEPTSIZ; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_OTG_DCFG_DAD ; 
 int /*<<< orphan*/  USB_OTG_DCTL_CGINAK ; 
 unsigned int USB_OTG_DOEPTSIZ_PKTCNT ; 
 unsigned int USB_OTG_DOEPTSIZ_STUPCNT ; 
 int USB_OTG_GRSTCTL_RXFFLSH ; 
 int USB_OTG_GRSTCTL_TXFFLSH ; 
 int USB_OTG_GRSTCTL_TXFNUM_4 ; 
 TYPE_4__* USBx ; 
 TYPE_3__* USBx_DEVICE ; 
 TYPE_2__* USBx_INEP (int /*<<< orphan*/ ) ; 
 TYPE_1__* USBx_OUTEP (int /*<<< orphan*/ ) ; 

void usb_reset(void) {
  // unmask endpoint interrupts, so many sets
  USBx_DEVICE->DAINT = 0xFFFFFFFF;
  USBx_DEVICE->DAINTMSK = 0xFFFFFFFF;
  //USBx_DEVICE->DOEPMSK = (USB_OTG_DOEPMSK_STUPM | USB_OTG_DOEPMSK_XFRCM | USB_OTG_DOEPMSK_EPDM);
  //USBx_DEVICE->DIEPMSK = (USB_OTG_DIEPMSK_TOM | USB_OTG_DIEPMSK_XFRCM | USB_OTG_DIEPMSK_EPDM | USB_OTG_DIEPMSK_ITTXFEMSK);
  //USBx_DEVICE->DIEPMSK = (USB_OTG_DIEPMSK_TOM | USB_OTG_DIEPMSK_XFRCM | USB_OTG_DIEPMSK_EPDM);

  // all interrupts for debugging
  USBx_DEVICE->DIEPMSK = 0xFFFFFFFF;
  USBx_DEVICE->DOEPMSK = 0xFFFFFFFF;

  // clear interrupts
  USBx_INEP(0)->DIEPINT = 0xFF;
  USBx_OUTEP(0)->DOEPINT = 0xFF;

  // unset the address
  USBx_DEVICE->DCFG &= ~USB_OTG_DCFG_DAD;

  // set up USB FIFOs
  // RX start address is fixed to 0
  USBx->GRXFSIZ = 0x40;

  // 0x100 to offset past GRXFSIZ
  USBx->DIEPTXF0_HNPTXFSIZ = (0x40U << 16) | 0x40U;

  // EP1, massive
  USBx->DIEPTXF[0] = (0x40U << 16) | 0x80U;

  // flush TX fifo
  USBx->GRSTCTL = USB_OTG_GRSTCTL_TXFFLSH | USB_OTG_GRSTCTL_TXFNUM_4;
  while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_TXFFLSH) == USB_OTG_GRSTCTL_TXFFLSH);
  // flush RX FIFO
  USBx->GRSTCTL = USB_OTG_GRSTCTL_RXFFLSH;
  while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_RXFFLSH) == USB_OTG_GRSTCTL_RXFFLSH);

  // no global NAK
  USBx_DEVICE->DCTL |= USB_OTG_DCTL_CGINAK;

  // ready to receive setup packets
  USBx_OUTEP(0)->DOEPTSIZ = USB_OTG_DOEPTSIZ_STUPCNT | (USB_OTG_DOEPTSIZ_PKTCNT & (1U << 19)) | (3U << 3);
}