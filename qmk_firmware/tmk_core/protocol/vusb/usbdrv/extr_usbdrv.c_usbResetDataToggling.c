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
 int /*<<< orphan*/  USB_INITIAL_DATATOKEN ; 
 int /*<<< orphan*/  USB_SET_DATATOKEN1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_SET_DATATOKEN3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void usbResetDataToggling(void) {
#if USB_CFG_HAVE_INTRIN_ENDPOINT && !USB_CFG_SUPPRESS_INTR_CODE
    USB_SET_DATATOKEN1(USB_INITIAL_DATATOKEN); /* reset data toggling for interrupt endpoint */
#    if USB_CFG_HAVE_INTRIN_ENDPOINT3
    USB_SET_DATATOKEN3(USB_INITIAL_DATATOKEN); /* reset data toggling for interrupt endpoint */
#    endif
#endif
}