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
struct TYPE_4__ {unsigned int leds; int layer; } ;
struct TYPE_5__ {char* layer_text; void* target_lcd_color; TYPE_1__ status; } ;
typedef  TYPE_2__ visualizer_state_t ;
typedef  int uint8_t ;

/* Variables and functions */
 void* LCD_COLOR (int,int,int) ; 
 unsigned int USB_LED_CAPS_LOCK ; 

__attribute__((used)) static void get_visualizer_layer_and_color(visualizer_state_t* state) {
    uint8_t saturation = 60;
    if (state->status.leds & (1u << USB_LED_CAPS_LOCK)) {
        saturation = 255;
    }

    if (state->status.layer & 0x4) {
        state->target_lcd_color = LCD_COLOR(0, saturation, 0xFF);
        state->layer_text = "Media";
    }
    else if (state->status.layer & 0x2) {
        state->target_lcd_color = LCD_COLOR(168, saturation, 0xFF);
        state->layer_text = "Symbols";
    }
    else {
        state->target_lcd_color = LCD_COLOR(84, saturation, 0xFF);
        state->layer_text = "Base";
    }
}