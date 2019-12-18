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
typedef  int uint8_t ;

/* Variables and functions */
#define  FKEYS 133 
 void* LCD_COLOR (int,int,int) ; 
#define  NEO_3 132 
#define  NEO_4 131 
#define  NEO_5 130 
#define  NEO_6 129 
#define  US_1 128 
 int biton32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_visualizer_layer_and_color(visualizer_state_t *state) {
  uint8_t layer = biton32(state->status.layer);

  // Go from highest to lowest layer to get the right text/color combination.
  switch (layer) {
    // #AEB2F4 / hsv(65.71%, 28.69%, 95.69%)
    case FKEYS:
      // #F4AEDC / hsv(89.05%, 28.69%, 95.69%)
      state->layer_text       = "FUNCTION KEYS";
      state->target_lcd_color = LCD_COLOR(228, 73, 245);
      break;
    case US_1:
      // #F4B993 / hsv(6.53%, 39.75%, 95.69%)
      state->layer_text       = "QWERTY";
      state->target_lcd_color = LCD_COLOR(17, 102, 245);
      break;
    case NEO_6:
      // #F4E393 / hsv(13.75%, 39.75%, 95.69%)
      state->layer_text       = "NEO: 6";
      state->target_lcd_color = LCD_COLOR(35, 102, 245);
      break;
    case NEO_5:
      // #C6F493 / hsv(24.57%, 39.75%, 95.69%)
      state->layer_text       = "NEO: 5";
      state->target_lcd_color = LCD_COLOR(63, 102, 245);
      break;
    case NEO_4:
      // #8EEBC9 / hsv(43.91%, 39.57%, 92.16%)
      state->layer_text       = "NEO: 4";
      state->target_lcd_color = LCD_COLOR(112, 101, 189);
      break;
    case NEO_3:
      // #93D2F4 / hsv(55.84%, 39.75%, 95.69%)
      state->layer_text       = "NEO: 3";
      state->target_lcd_color = LCD_COLOR(143, 102, 245);
      break;
    default:
      // #EEEEEE / hsv(0%, 0%, 93%)
      state->layer_text       = "NEO: 1";
      state->target_lcd_color = LCD_COLOR(0, 0, 255);
      break;
  }
}