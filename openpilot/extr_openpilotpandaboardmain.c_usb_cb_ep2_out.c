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
typedef  int /*<<< orphan*/  uart_ring ;

/* Variables and functions */
 int /*<<< orphan*/  esp_ring ; 
 int /*<<< orphan*/ * get_ring_by_number (int) ; 
 int /*<<< orphan*/  power_save_reset_timer () ; 
 int /*<<< orphan*/  putc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ safety_tx_lin_hook (int,int*,int) ; 

void usb_cb_ep2_out(uint8_t *usbdata, int len, int hardwired) {
  if (len == 0) return;
  uart_ring *ur = get_ring_by_number(usbdata[0]);
  if (!ur) return;
  if ((usbdata[0] < 2) || safety_tx_lin_hook(usbdata[0]-2, usbdata+1, len-1)) {
    if (ur == &esp_ring) power_save_reset_timer();
    for (int i = 1; i < len; i++) while (!putc(ur, usbdata[i]));
  }
}