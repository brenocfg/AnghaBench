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
typedef  int /*<<< orphan*/  USB_Setup_TypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (int) ; 
 int usb_cb_control_msg (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_cb_ep2_out (int*,int,int /*<<< orphan*/ ) ; 

int spi_cb_rx(uint8_t *data, int len, uint8_t *data_out) {
  UNUSED(len);
  int resp_len = 0;
  switch (data[0]) {
    case 0:
      // control transfer
      resp_len = usb_cb_control_msg((USB_Setup_TypeDef *)(data+4), data_out, 0);
      break;
    case 2:
      // ep 2, flash!
      usb_cb_ep2_out(data+4, data[2], 0);
      break;
  }
  return resp_len;
}