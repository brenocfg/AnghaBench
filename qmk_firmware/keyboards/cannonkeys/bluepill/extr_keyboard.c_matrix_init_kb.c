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
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  LED_OFF () ; 
 int /*<<< orphan*/  LED_ON () ; 
 int /*<<< orphan*/  PAL_MODE_STM32_ALTERNATE_PUSHPULL ; 
 int /*<<< orphan*/  leds_init () ; 
 int /*<<< orphan*/  palSetPadMode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_ms (int) ; 

void matrix_init_kb(void){
      /* MOSI pin*/
    palSetPadMode(GPIOB, 15, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    LED_ON();
    wait_ms(500);
    LED_OFF();

#ifdef RGBLIGHT_ENABLE
    leds_init();
#endif
}