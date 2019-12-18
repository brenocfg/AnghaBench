#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int leds; } ;
struct TYPE_5__ {TYPE_1__ status; } ;
typedef  TYPE_2__ visualizer_state_t ;
typedef  int uint8_t ;

/* Variables and functions */
 unsigned int USB_LED_CAPS_LOCK ; 
 unsigned int USB_LED_COMPOSE ; 
 unsigned int USB_LED_KANA ; 
 unsigned int USB_LED_NUM_LOCK ; 
 unsigned int USB_LED_SCROLL_LOCK ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static void get_led_state_string(char* output, visualizer_state_t* state) {
    uint8_t pos = 0;

    if (state->status.leds & (1u << USB_LED_NUM_LOCK)) {
        memcpy(output + pos, "NUM ", 4);
        pos += 4;
    }
    if (state->status.leds & (1u << USB_LED_CAPS_LOCK)) {
        memcpy(output + pos, "CAPS ", 5);
        pos += 5;
    }
    if (state->status.leds & (1u << USB_LED_SCROLL_LOCK)) {
        memcpy(output + pos, "SCRL ", 5);
        pos += 5;
    }
    if (state->status.leds & (1u << USB_LED_COMPOSE)) {
        memcpy(output + pos, "COMP ", 5);
        pos += 5;
    }
    if (state->status.leds & (1u << USB_LED_KANA)) {
        memcpy(output + pos, "KANA", 4);
        pos += 4;
    }
    output[pos] = 0;
}