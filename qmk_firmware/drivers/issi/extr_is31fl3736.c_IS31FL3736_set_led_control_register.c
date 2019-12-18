#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_3__ {int r; int g; int b; size_t driver; } ;
typedef  TYPE_1__ is31_led ;

/* Variables and functions */
 TYPE_1__* g_is31_leds ; 
 int** g_led_control_registers ; 
 int g_led_control_registers_update_required ; 

void IS31FL3736_set_led_control_register(uint8_t index, bool red, bool green, bool blue) {
    is31_led led = g_is31_leds[index];

    // IS31FL3733
    // The PWM register for a matrix position (0x00 to 0xBF) can be
    // divided by 8 to get the LED control register (0x00 to 0x17),
    // then mod 8 to get the bit position within that register.

    // IS31FL3736
    // The PWM register for a matrix position (0x00 to 0xBF) is interleaved, so:
    // A1=0x00 A2=0x02 A3=0x04 A4=0x06 A5=0x08 A6=0x0A A7=0x0C A8=0x0E
    // B1=0x10 B2=0x12 B3=0x14
    // But also, the LED control registers (0x00 to 0x17) are also interleaved, so:
    // A1-A4=0x00 A5-A8=0x01
    // So, the same math applies.

    uint8_t control_register_r = led.r / 8;
    uint8_t control_register_g = led.g / 8;
    uint8_t control_register_b = led.b / 8;

    uint8_t bit_r = led.r % 8;
    uint8_t bit_g = led.g % 8;
    uint8_t bit_b = led.b % 8;

    if (red) {
        g_led_control_registers[led.driver][control_register_r] |= (1 << bit_r);
    } else {
        g_led_control_registers[led.driver][control_register_r] &= ~(1 << bit_r);
    }
    if (green) {
        g_led_control_registers[led.driver][control_register_g] |= (1 << bit_g);
    } else {
        g_led_control_registers[led.driver][control_register_g] &= ~(1 << bit_g);
    }
    if (blue) {
        g_led_control_registers[led.driver][control_register_b] |= (1 << bit_b);
    } else {
        g_led_control_registers[led.driver][control_register_b] &= ~(1 << bit_b);
    }

    g_led_control_registers_update_required = true;
}