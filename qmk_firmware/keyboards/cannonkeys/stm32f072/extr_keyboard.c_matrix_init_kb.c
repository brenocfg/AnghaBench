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
 int /*<<< orphan*/  PAL_MODE_ALTERNATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIN_WS2812 ; 
 int /*<<< orphan*/  PORT_WS2812 ; 
 int /*<<< orphan*/  backlight_init_ports () ; 
 int /*<<< orphan*/  eeprom_init_kb () ; 
 int /*<<< orphan*/  leds_init () ; 
 int /*<<< orphan*/  matrix_init_board () ; 
 int /*<<< orphan*/  palSetPadMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void matrix_init_kb(void){
  	eeprom_init_kb();
      /* MOSI pin*/
#ifdef RGBLIGHT_ENABLE
    palSetPadMode(PORT_WS2812, PIN_WS2812, PAL_MODE_ALTERNATE(0));
    wait_ms(500);
    leds_init();
#endif
    backlight_init_ports();

    matrix_init_board();
}