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
 int /*<<< orphan*/  TWI_BITLENGTH_FROM_FREQ (int,int) ; 
 int /*<<< orphan*/  TWI_BIT_PRESCALE_1 ; 
 int /*<<< orphan*/  TWI_Init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  i2c_master_init () ; 
 int /*<<< orphan*/  iota_gfx_init () ; 
 int /*<<< orphan*/  startup_user () ; 

void matrix_init_user(void) {
  #ifdef USE_I2C
    i2c_master_init();
  #ifdef SSD1306OLED
  // calls code for the SSD1306 OLED
        _delay_ms(400);
        TWI_Init(TWI_BIT_PRESCALE_1, TWI_BITLENGTH_FROM_FREQ(1, 800000));
        iota_gfx_init();   // turns on the display
  #endif
  #endif
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
}