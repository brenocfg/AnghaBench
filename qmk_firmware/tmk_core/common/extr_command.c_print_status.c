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
struct TYPE_2__ {int /*<<< orphan*/  nkro; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDCON ; 
 int /*<<< orphan*/  UDIEN ; 
 int /*<<< orphan*/  UDINT ; 
 int /*<<< orphan*/  host_keyboard_leds () ; 
 int /*<<< orphan*/  keyboard_idle ; 
 int /*<<< orphan*/  keyboard_protocol ; 
 TYPE_1__ keymap_config ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  print_val_hex32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_val_hex8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read32 () ; 
 int /*<<< orphan*/  usbSofCount ; 
 int /*<<< orphan*/  usb_keyboard_idle_count ; 
 int /*<<< orphan*/  usb_keyboard_leds ; 

__attribute__((used)) static void print_status(void) {
    print("\n\t- Status -\n");

    print_val_hex8(host_keyboard_leds());
#ifndef PROTOCOL_VUSB
    // these aren't set on the V-USB protocol, so we just ignore them for now
    print_val_hex8(keyboard_protocol);
    print_val_hex8(keyboard_idle);
#endif
#ifdef NKRO_ENABLE
    print_val_hex8(keymap_config.nkro);
#endif
    print_val_hex32(timer_read32());

#ifdef PROTOCOL_PJRC
    print_val_hex8(UDCON);
    print_val_hex8(UDIEN);
    print_val_hex8(UDINT);
    print_val_hex8(usb_keyboard_leds);
    print_val_hex8(usb_keyboard_idle_count);
#endif

#ifdef PROTOCOL_PJRC
#    if USB_COUNT_SOF
    print_val_hex8(usbSofCount);
#    endif
#endif
    return;
}