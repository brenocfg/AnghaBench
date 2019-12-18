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
 int /*<<< orphan*/  USB_Disable () ; 
 int /*<<< orphan*/  USB_Init () ; 
 int /*<<< orphan*/  serial_send (char) ; 

void print_char(char c) {
    USB_Disable();
    serial_send(c);
    USB_Init();
}