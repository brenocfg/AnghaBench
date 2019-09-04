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
typedef  int uint32_t ;
struct TYPE_4__ {int GRSTCTL; int GUSBCFG; int GCCFG; int GINTSTS; int GINTMSK; int /*<<< orphan*/  GAHBCFG; } ;
struct TYPE_3__ {int DCFG; scalar_t__ DCTL; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OTG_FS_IRQn ; 
 int USBD_FS_TRDT_VALUE ; 
 int USB_OTG_DCFG_NZLSOHSK ; 
 int /*<<< orphan*/  USB_OTG_GAHBCFG_GINT ; 
 int USB_OTG_GCCFG_NOVBUSSENS ; 
 int USB_OTG_GCCFG_PWRDWN ; 
 int USB_OTG_GINTMSK_CIDSCHGM ; 
 int USB_OTG_GINTMSK_ENUMDNEM ; 
 int USB_OTG_GINTMSK_GINAKEFFM ; 
 int USB_OTG_GINTMSK_GONAKEFFM ; 
 int USB_OTG_GINTMSK_IEPINT ; 
 int USB_OTG_GINTMSK_MMISM ; 
 int USB_OTG_GINTMSK_OEPINT ; 
 int USB_OTG_GINTMSK_OTGINT ; 
 int USB_OTG_GINTMSK_RXFLVLM ; 
 int USB_OTG_GINTMSK_SRQIM ; 
 int USB_OTG_GINTMSK_USBRST ; 
 int USB_OTG_GINTMSK_USBSUSPM ; 
 int USB_OTG_GRSTCTL_AHBIDL ; 
 int USB_OTG_GRSTCTL_CSRST ; 
 int USB_OTG_GUSBCFG_FDMOD ; 
 int USB_OTG_GUSBCFG_PHYSEL ; 
 int USB_OTG_GUSBCFG_TRDT ; 
 int USB_OTG_SPEED_FULL ; 
 TYPE_2__* USBx ; 
 TYPE_1__* USBx_DEVICE ; 
 scalar_t__ USBx_PCGCCTL ; 

void usb_init() {
  // full speed PHY, do reset and remove power down
  /*puth(USBx->GRSTCTL);
  puts(" resetting PHY\n");*/
  while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_AHBIDL) == 0);
  //puts("AHB idle\n");

  // reset PHY here
  USBx->GRSTCTL |= USB_OTG_GRSTCTL_CSRST;
  while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_CSRST) == USB_OTG_GRSTCTL_CSRST);
  //puts("reset done\n");

  // internal PHY, force device mode
  USBx->GUSBCFG = USB_OTG_GUSBCFG_PHYSEL | USB_OTG_GUSBCFG_FDMOD;

  // slowest timings
  USBx->GUSBCFG |= (uint32_t)((USBD_FS_TRDT_VALUE << 10) & USB_OTG_GUSBCFG_TRDT);

  // power up the PHY
#ifdef STM32F4
  USBx->GCCFG = USB_OTG_GCCFG_PWRDWN;

  //USBx->GCCFG |= USB_OTG_GCCFG_VBDEN | USB_OTG_GCCFG_SDEN |USB_OTG_GCCFG_PDEN | USB_OTG_GCCFG_DCDEN;

  /* B-peripheral session valid override enable*/
  USBx->GOTGCTL |= USB_OTG_GOTGCTL_BVALOVAL;
  USBx->GOTGCTL |= USB_OTG_GOTGCTL_BVALOEN;
#else
  USBx->GCCFG = USB_OTG_GCCFG_PWRDWN | USB_OTG_GCCFG_NOVBUSSENS;
#endif

  // be a device, slowest timings
  //USBx->GUSBCFG = USB_OTG_GUSBCFG_FDMOD | USB_OTG_GUSBCFG_PHYSEL | USB_OTG_GUSBCFG_TRDT | USB_OTG_GUSBCFG_TOCAL;
  //USBx->GUSBCFG |= (uint32_t)((USBD_FS_TRDT_VALUE << 10) & USB_OTG_GUSBCFG_TRDT);
  //USBx->GUSBCFG = USB_OTG_GUSBCFG_PHYSEL | USB_OTG_GUSBCFG_TRDT | USB_OTG_GUSBCFG_TOCAL;

  // **** for debugging, doesn't seem to work ****
  //USBx->GUSBCFG |= USB_OTG_GUSBCFG_CTXPKT;

  // reset PHY clock
  USBx_PCGCCTL = 0;

  // enable the fancy OTG things
  // DCFG_FRAME_INTERVAL_80 is 0
  //USBx->GUSBCFG |= USB_OTG_GUSBCFG_HNPCAP | USB_OTG_GUSBCFG_SRPCAP;
  USBx_DEVICE->DCFG |= USB_OTG_SPEED_FULL | USB_OTG_DCFG_NZLSOHSK;

  //USBx_DEVICE->DCFG = USB_OTG_DCFG_NZLSOHSK | USB_OTG_DCFG_DSPD;
  //USBx_DEVICE->DCFG = USB_OTG_DCFG_DSPD;

  // clear pending interrupts
  USBx->GINTSTS = 0xBFFFFFFFU;

  // setup USB interrupts
  // all interrupts except TXFIFO EMPTY
  //USBx->GINTMSK = 0xFFFFFFFF & ~(USB_OTG_GINTMSK_NPTXFEM | USB_OTG_GINTMSK_PTXFEM | USB_OTG_GINTSTS_SOF | USB_OTG_GINTSTS_EOPF);
  //USBx->GINTMSK = 0xFFFFFFFF & ~(USB_OTG_GINTMSK_NPTXFEM | USB_OTG_GINTMSK_PTXFEM);
  USBx->GINTMSK = USB_OTG_GINTMSK_USBRST | USB_OTG_GINTMSK_ENUMDNEM | USB_OTG_GINTMSK_OTGINT |
                  USB_OTG_GINTMSK_RXFLVLM | USB_OTG_GINTMSK_GONAKEFFM | USB_OTG_GINTMSK_GINAKEFFM |
                  USB_OTG_GINTMSK_OEPINT | USB_OTG_GINTMSK_IEPINT | USB_OTG_GINTMSK_USBSUSPM |
                  USB_OTG_GINTMSK_CIDSCHGM | USB_OTG_GINTMSK_SRQIM | USB_OTG_GINTMSK_MMISM;

  USBx->GAHBCFG = USB_OTG_GAHBCFG_GINT;

  // DCTL startup value is 2 on new chip, 0 on old chip
  // THIS IS FUCKING BULLSHIT
  USBx_DEVICE->DCTL = 0;

  // enable the IRQ
  NVIC_EnableIRQ(OTG_FS_IRQn);
}