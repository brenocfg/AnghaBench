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

/* Variables and functions */
 void* USBPID_NAK ; 
 int /*<<< orphan*/  USB_INTR_CFG ; 
 int /*<<< orphan*/  USB_INTR_CFG_CLR ; 
 int /*<<< orphan*/  USB_INTR_CFG_SET ; 
 int USB_INTR_ENABLE ; 
 int USB_INTR_ENABLE_BIT ; 
 int /*<<< orphan*/  usbResetDataToggling () ; 
 void* usbTxLen1 ; 
 void* usbTxLen3 ; 

void usbInit(void) {
#if USB_INTR_CFG_SET != 0
    USB_INTR_CFG |= USB_INTR_CFG_SET;
#endif
#if USB_INTR_CFG_CLR != 0
    USB_INTR_CFG &= ~(USB_INTR_CFG_CLR);
#endif
    USB_INTR_ENABLE |= (1 << USB_INTR_ENABLE_BIT);
    usbResetDataToggling();
#if USB_CFG_HAVE_INTRIN_ENDPOINT && !USB_CFG_SUPPRESS_INTR_CODE
    usbTxLen1 = USBPID_NAK;
#    if USB_CFG_HAVE_INTRIN_ENDPOINT3
    usbTxLen3 = USBPID_NAK;
#    endif
#endif
}