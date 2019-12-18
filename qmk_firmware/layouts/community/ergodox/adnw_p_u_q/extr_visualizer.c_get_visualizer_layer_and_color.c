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
struct TYPE_4__ {int layer; } ;
struct TYPE_5__ {char* layer_text; void* target_lcd_color; TYPE_1__ status; } ;
typedef  TYPE_2__ visualizer_state_t ;

/* Variables and functions */
 void* LCD_COLOR (int,int,int) ; 

__attribute__((used)) static void get_visualizer_layer_and_color(visualizer_state_t* state) {

    if (state->status.layer & 0x20) {
        state->target_lcd_color = LCD_COLOR(127, 0xFF, 0xFF);
        state->layer_text = "Mouse";
    } else if (state->status.layer & 0x10) {
        state->target_lcd_color = LCD_COLOR(85, 0xFF, 0xFF);
        state->layer_text = "Symbol";
    } else if (state->status.layer & 0x8) {
        state->target_lcd_color = LCD_COLOR(64, 0xFF, 0xFF);
        state->layer_text = "Brackets";
    } else if (state->status.layer & 0x4) {
        state->target_lcd_color = LCD_COLOR(42, 0xFF, 0xFF);
        state->layer_text = "Diak";
    } else if (state->status.layer & 0x2) {
        state->target_lcd_color = LCD_COLOR(21, 0xFF, 0xFF);
        state->layer_text = "Terminal";
    } else {
        state->target_lcd_color = LCD_COLOR(192, 0xFF, 0xFF);
        state->layer_text = "Vim";
    }
}