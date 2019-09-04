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
 int /*<<< orphan*/  usb_serial_putchar (char const) ; 

void usb_vcp_send_strn_cooked(const char *str, int len)
{
  for (const char *top = str + len; str < top; str++) {
    if (*str == '\n') {
      usb_serial_putchar('\r');
    }
    usb_serial_putchar(*str);
  }
}