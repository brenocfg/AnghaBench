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
struct TYPE_5__ {char* layer_text; void* target_lcd_color; TYPE_1__ status; } ;
typedef  TYPE_2__ visualizer_state_t ;

/* Variables and functions */
 void* LCD_COLOR (int,int,int) ; 
#define  _ADJUST 137 
#define  _COLEMAK 136 
#define  _DVORAK 135 
#define  _GAME 134 
#define  _LOWER 133 
#define  _MOUSE 132 
#define  _NUM 131 
#define  _QWERTY 130 
#define  _RAISE 129 
#define  _WORKMAN 128 
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_layer_state ; 

__attribute__((used)) static void get_visualizer_layer_and_color(visualizer_state_t* state) {
  switch(biton32(default_layer_state)) {
    case _QWERTY:
      state->layer_text = "QWERTY";
      state->target_lcd_color = LCD_COLOR(0, 255, 128);
      break;
    case _WORKMAN:
      state->layer_text = "Workman";
      state->target_lcd_color = LCD_COLOR(80, 255, 128);
      break;
    case _DVORAK:
      state->layer_text = "Dvorak";
      state->target_lcd_color = LCD_COLOR(194, 255, 128);
      break;
    case _COLEMAK:
      state->layer_text = "Colemak";
      state->target_lcd_color = LCD_COLOR(18, 255, 128);
      break;
  }

  switch(biton32(state->status.layer)) {
    case _LOWER:
      state->layer_text = "Lower";
      state->target_lcd_color = LCD_COLOR(141, 255, 255);
      break;
    case _RAISE:
      state->layer_text = "Raise";
      state->target_lcd_color = LCD_COLOR(18, 255, 255);
      break;
    case _ADJUST:
      state->layer_text = "Adjust";
      state->target_lcd_color = LCD_COLOR(194, 255, 255);
      break;
    case _NUM:
      state->layer_text = "Numpad";
      state->target_lcd_color = LCD_COLOR(80, 255, 255);
      break;
    case _MOUSE:
      state->layer_text = "Mouse";
      state->target_lcd_color = LCD_COLOR(300, 255, 255);
      break;
    case _GAME:
      state->layer_text = "Game";
      state->target_lcd_color = LCD_COLOR(300, 255, 255);
      break;
    case _QWERTY: case _WORKMAN: case _DVORAK: case _COLEMAK:
      break;
    default:
      state->layer_text = "NONE";
      state->target_lcd_color = LCD_COLOR(0, 255, 255);
      break;
  }
}