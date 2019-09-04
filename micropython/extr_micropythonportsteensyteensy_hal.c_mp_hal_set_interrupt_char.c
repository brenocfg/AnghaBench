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

void mp_hal_set_interrupt_char(int c) {
  // The teensy 3.1 usb stack doesn't currently have the notion of generating
  // an exception when a certain character is received. That just means that
  // you can't press Control-C and get your python script to stop.
}