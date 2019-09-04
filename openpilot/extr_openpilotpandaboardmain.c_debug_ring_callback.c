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
typedef  int /*<<< orphan*/  uart_ring ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER_BOOTLOADER_MAGIC ; 
 int /*<<< orphan*/  NVIC_SystemReset () ; 
 int /*<<< orphan*/  USB_POWER_CDP ; 
 int /*<<< orphan*/  USB_POWER_CLIENT ; 
 int /*<<< orphan*/  USB_POWER_DCP ; 
 int /*<<< orphan*/  enter_bootloader_mode ; 
 scalar_t__ getc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  putc (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  set_usb_power_mode (int /*<<< orphan*/ ) ; 

void debug_ring_callback(uart_ring *ring) {
  char rcv;
  while (getc(ring, &rcv)) {
    putc(ring, rcv);

    // jump to DFU flash
    if (rcv == 'z') {
      enter_bootloader_mode = ENTER_BOOTLOADER_MAGIC;
      NVIC_SystemReset();
    }

    // normal reset
    if (rcv == 'x') {
      NVIC_SystemReset();
    }

    // enable CDP mode
    if (rcv == 'C') {
      puts("switching USB to CDP mode\n");
      set_usb_power_mode(USB_POWER_CDP);
    }
    if (rcv == 'c') {
      puts("switching USB to client mode\n");
      set_usb_power_mode(USB_POWER_CLIENT);
    }
    if (rcv == 'D') {
      puts("switching USB to DCP mode\n");
      set_usb_power_mode(USB_POWER_DCP);
    }
  }
}