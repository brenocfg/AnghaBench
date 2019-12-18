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
typedef  scalar_t__ int8_t ;

/* Variables and functions */
#define  ENC_MODE_BACKLIGHT 136 
#define  ENC_MODE_BRIGHTNESS 135 
#define  ENC_MODE_CLOCK_SET 134 
#define  ENC_MODE_CUSTOM0 133 
#define  ENC_MODE_CUSTOM1 132 
#define  ENC_MODE_CUSTOM2 131 
#define  ENC_MODE_MEDIA 130 
#define  ENC_MODE_SCROLL 129 
#define  ENC_MODE_VOLUME 128 
 int /*<<< orphan*/  NORM ; 
 int /*<<< orphan*/  PIXEL_ON ; 
 int /*<<< orphan*/  XOR ; 
 int /*<<< orphan*/  draw_rect_filled_soft (scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_string (scalar_t__,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int encoder_mode ; 

void draw_encoder(int8_t startX, int8_t startY, bool show_legend){
  if(show_legend){
    draw_string(startX + 1, startY + 2, "ENC", PIXEL_ON, NORM, 0);
  } else {
    startX -= 22;
  }
  draw_rect_filled_soft(startX + 22, startY + 1, 3 + (3 * 6), 9, PIXEL_ON, NORM);
  char* mode_string = "";
  switch(encoder_mode){
    default:
    case ENC_MODE_VOLUME:
      mode_string = "VOL";
      break;
    case ENC_MODE_MEDIA:
      mode_string = "MED";
      break;
    case ENC_MODE_SCROLL:
      mode_string = "SCR";
      break;
    case ENC_MODE_BRIGHTNESS:
      mode_string = "BRT";
      break;
    case ENC_MODE_BACKLIGHT:
      mode_string = "BKL";
      break;
    case ENC_MODE_CLOCK_SET:
      mode_string = "CLK";
      break;
    case ENC_MODE_CUSTOM0:
      mode_string = "CS0";
      break;
    case ENC_MODE_CUSTOM1:
      mode_string = "CS1";
      break;
    case ENC_MODE_CUSTOM2:
      mode_string = "CS2";
      break;
  }
  draw_string(startX + 24, startY + 2, mode_string, PIXEL_ON, XOR, 0);
}