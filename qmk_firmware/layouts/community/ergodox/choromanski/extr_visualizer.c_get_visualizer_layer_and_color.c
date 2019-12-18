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
        //GREEN
        state->target_lcd_color = LCD_COLOR(85, 255, 128);
        state->layer_text = "Gaming";
    }
    else if (state->status.layer & 0x10) {
        //ORANGE
        state->target_lcd_color = LCD_COLOR(28, 255, 230);
        state->layer_text = "Numpad & Mouse";
    }
    else if (state->status.layer & 0x8) {
        //YELLOW
        state->target_lcd_color = LCD_COLOR(38, 255, 230);
        state->layer_text = "Symbols";
    }
    else if (state->status.layer & 0x4) {
        //RED
        state->target_lcd_color = LCD_COLOR(0, 255, 95);
        if (state->status.layer & 0x2){
            state->layer_text = "Qwerty - Fn";
        }else{
            state->layer_text = "Colemak - Fn";
        }
    }
    else if (state->status.layer & 0x2) {
        //BLUE
        state->target_lcd_color = LCD_COLOR(149, 255, 192);
        state->layer_text = "Qwerty";
    }
    else {
        //PURPLE
        state->target_lcd_color = LCD_COLOR(200, 255, 192);
        state->layer_text = "Colemak";
    }
}