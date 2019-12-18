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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ OUTPUT_BLUETOOTH ; 
 scalar_t__ OUTPUT_USB ; 
 int /*<<< orphan*/  UC_LNX ; 
 scalar_t__ auto_detect_output () ; 
 int /*<<< orphan*/  led_init () ; 
 int /*<<< orphan*/  set_output (scalar_t__) ; 
 int /*<<< orphan*/  set_unicode_input_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void matrix_init_user() {
  wait_ms(500); // give time for usb to initialize

  set_unicode_input_mode(UC_LNX);

#ifdef RGBSPS_ENABLE
  led_init();
#endif

  // auto detect output on init
#ifdef MODULE_ADAFRUIT_BLE
  uint8_t output = auto_detect_output();
  if (output == OUTPUT_USB) {
    set_output(OUTPUT_USB);
  } else {
    set_output(OUTPUT_BLUETOOTH);
  }
#endif
}