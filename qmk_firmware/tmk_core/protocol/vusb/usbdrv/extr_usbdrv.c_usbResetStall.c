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
 void* usbTxLen1 ; 
 void* usbTxLen3 ; 

__attribute__((used)) static inline void usbResetStall(void) {
#if USB_CFG_IMPLEMENT_HALT && USB_CFG_HAVE_INTRIN_ENDPOINT
    usbTxLen1 = USBPID_NAK;
#    if USB_CFG_HAVE_INTRIN_ENDPOINT3
    usbTxLen3 = USBPID_NAK;
#    endif
#endif
}