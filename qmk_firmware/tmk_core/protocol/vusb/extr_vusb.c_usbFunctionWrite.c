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
typedef  int uchar ;
struct TYPE_2__ {scalar_t__ len; int kind; } ;

/* Variables and functions */
#define  BOOTLOADER 130 
#define  NONE 129 
#define  SET_LED 128 
 int /*<<< orphan*/  bootloader_jump () ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug_hex (int) ; 
 TYPE_1__ last_req ; 
 int /*<<< orphan*/  usbDeviceDisconnect () ; 
 int vusb_keyboard_leds ; 

uchar usbFunctionWrite(uchar *data, uchar len) {
    if (last_req.len == 0) {
        return -1;
    }
    switch (last_req.kind) {
        case SET_LED:
            debug("SET_LED: ");
            debug_hex(data[0]);
            debug("\n");
            vusb_keyboard_leds = data[0];
            last_req.len       = 0;
            return 1;
            break;
        case BOOTLOADER:
            usbDeviceDisconnect();
            bootloader_jump();
            return 1;
            break;
        case NONE:
        default:
            return -1;
            break;
    }
    return 1;
}