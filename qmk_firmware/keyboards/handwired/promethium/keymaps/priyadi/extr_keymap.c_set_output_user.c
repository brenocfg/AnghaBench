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
#define  OUTPUT_BLUETOOTH 129 
#define  OUTPUT_USB 128 
 int /*<<< orphan*/  led_set_output_ble () ; 
 int /*<<< orphan*/  led_set_output_none () ; 
 int /*<<< orphan*/  led_set_output_usb () ; 

void set_output_user(uint8_t output) {
#ifdef MODULE_ADAFRUIT_BLE
  switch(output) {
    case OUTPUT_USB:
      led_set_output_usb();
      break;
    case OUTPUT_BLUETOOTH:
      led_set_output_ble();
      break;
    default:
      led_set_output_none();
  }
#endif
}