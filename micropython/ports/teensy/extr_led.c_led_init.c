#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  gpio; int /*<<< orphan*/  pin_mask; } ;
typedef  TYPE_1__ pin_obj_t ;
struct TYPE_8__ {TYPE_1__* led_pin; } ;
struct TYPE_7__ {int /*<<< orphan*/  Pin; int /*<<< orphan*/  Pull; int /*<<< orphan*/  Mode; int /*<<< orphan*/  Speed; } ;
typedef  TYPE_2__ GPIO_InitTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_NOPULL ; 
 int /*<<< orphan*/  GPIO_SPEED_FREQ_LOW ; 
 int /*<<< orphan*/  HAL_GPIO_Init (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  MICROPY_HW_LED_OFF (TYPE_1__ const*) ; 
 int /*<<< orphan*/  MICROPY_HW_LED_OTYPE ; 
 int NUM_LEDS ; 
 TYPE_3__* pyb_led_obj ; 

void led_init(void) {
    /* GPIO structure */
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Configure I/O speed, mode, output type and pull */
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStructure.Mode = MICROPY_HW_LED_OTYPE;
    GPIO_InitStructure.Pull = GPIO_NOPULL;

    /* Turn off LEDs and initialize */
    for (int led = 0; led < NUM_LEDS; led++) {
        const pin_obj_t *led_pin = pyb_led_obj[led].led_pin;
        MICROPY_HW_LED_OFF(led_pin);
        GPIO_InitStructure.Pin = led_pin->pin_mask;
        HAL_GPIO_Init(led_pin->gpio, &GPIO_InitStructure);
    }
}