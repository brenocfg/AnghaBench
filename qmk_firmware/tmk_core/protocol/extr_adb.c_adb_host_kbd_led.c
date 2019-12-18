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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  adb_host_listen (int,int /*<<< orphan*/ ,int) ; 

void adb_host_kbd_led(uint8_t led) {
    // Addr:Keyboard(0010), Cmd:Listen(10), Register2(10)
    // send upper byte (not used)
    // send lower byte (bit2: ScrollLock, bit1: CapsLock, bit0:
    adb_host_listen(0x2A, 0, led & 0x07);
}