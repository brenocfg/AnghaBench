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
struct TYPE_4__ {int /*<<< orphan*/  layer; } ;
struct TYPE_5__ {char* layer_text; int /*<<< orphan*/  target_lcd_color; TYPE_1__ status; } ;
typedef  TYPE_2__ visualizer_state_t ;
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCD_COLOR (int,int,int) ; 
#define  _ADJUST 140 
#define  _COLEMAK 139 
#define  _DUPER 138 
#define  _LOWER 137 
#define  _MDIA 136 
#define  _MOUSE 135 
#define  _PLOVER 134 
#define  _QWERTY 133 
#define  _QWOC 132 
#define  _RAISE 131 
#define  _SUPER 130 
#define  _SUPERDUPER 129 
#define  _SYMB 128 
 int biton32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_visualizer_layer_and_color(visualizer_state_t* state) {
    uint8_t saturation = 255;

    uint8_t layer = biton32(state->status.layer);
    state->target_lcd_color = LCD_COLOR(layer << 2, saturation, 0xFF);

    switch(layer) {
        case _QWERTY:
            state->layer_text = "QWERTY";
            break;
        case _COLEMAK:
            state->layer_text = "COLEMAK";
            break;
        case _QWOC:
            state->layer_text = "QWERTY on COLEMAK";
            break;
        case _LOWER:
            state->layer_text = "LOWER";
            break;
        case _RAISE:
            state->layer_text = "RAISE";
            break;
        case _PLOVER:
            state->layer_text = "PLOVER";
            break;
        case _SUPERDUPER:
            state->layer_text = "SUPERDUPER";
            break;
        case _SUPER:
            state->layer_text = "SUPER";
            break;
        case _DUPER:
            state->layer_text = "DUPER";
            break;
        case _MOUSE:
            state->layer_text = "MOUSE";
            break;
        case _ADJUST:
            state->layer_text = "ADJUST";
            break;
        case _MDIA:
            state->layer_text = "MDIA";
            break;
        case _SYMB:
            state->layer_text = "SYMB";
            break;
        default:
            state->layer_text = "NONE";
            break;
    }
}