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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  LED_TYPE ;

/* Variables and functions */
 int RGB_DI_PIN ; 
 int /*<<< orphan*/  _BV (int) ; 
 int /*<<< orphan*/  ws2812_setleds_pin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void inline ws2812_setleds(LED_TYPE *ledarray, uint16_t leds) {
    // ws2812_setleds_pin(ledarray,leds, _BV(ws2812_pin));
    ws2812_setleds_pin(ledarray, leds, _BV(RGB_DI_PIN & 0xF));
}