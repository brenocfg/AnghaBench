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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_mouse ; 
 int /*<<< orphan*/  phex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print (char*) ; 

void usb_mouse_print(int8_t x, int8_t y, int8_t wheel_v, int8_t wheel_h, uint8_t buttons) {
    if (!debug_mouse) return;
    print("usb_mouse[btn|x y v h]: ");
    phex(buttons);
    print("|");
    phex(x);
    print(" ");
    phex(y);
    print(" ");
    phex(wheel_v);
    print(" ");
    phex(wheel_h);
    print("\n");
}