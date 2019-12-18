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
typedef  scalar_t__ uchar ;

/* Variables and functions */
 int USB_FLG_MSGPTR_IS_ROM ; 
 int USB_FLG_USE_USER_RW ; 
 scalar_t__ USB_READ_FLASH (scalar_t__*) ; 
 scalar_t__ usbFunctionRead (scalar_t__*,scalar_t__) ; 
 int usbMsgFlags ; 
 scalar_t__* usbMsgPtr ; 

__attribute__((used)) static uchar usbDeviceRead(uchar *data, uchar len) {
    if (len > 0) { /* don't bother app with 0 sized reads */
#if USB_CFG_IMPLEMENT_FN_READ
        if (usbMsgFlags & USB_FLG_USE_USER_RW) {
            len = usbFunctionRead(data, len);
        } else
#endif
        {
            uchar i = len, *r = usbMsgPtr;
            if (usbMsgFlags & USB_FLG_MSGPTR_IS_ROM) { /* ROM data */
                do {
                    uchar c = USB_READ_FLASH(r); /* assign to char size variable to enforce byte ops */
                    *data++ = c;
                    r++;
                } while (--i);
            } else { /* RAM data */
                do {
                    *data++ = *r++;
                } while (--i);
            }
            usbMsgPtr = r;
        }
    }
    return len;
}