#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int breathing; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENC_CUSTOM_PRESS ; 
#define  ENC_MODE_BACKLIGHT 136 
#define  ENC_MODE_BRIGHTNESS 135 
#define  ENC_MODE_CLOCK_SET 134 
#define  ENC_MODE_CUSTOM0 133 
#define  ENC_MODE_CUSTOM1 132 
#define  ENC_MODE_CUSTOM2 131 
#define  ENC_MODE_MEDIA 130 
#define  ENC_MODE_SCROLL 129 
#define  ENC_MODE_VOLUME 128 
 int /*<<< orphan*/  KC_BTN3 ; 
 int /*<<< orphan*/  KC_MEDIA_PLAY_PAUSE ; 
 int /*<<< orphan*/  KC_MUTE ; 
 int /*<<< orphan*/  breathing_disable () ; 
 int /*<<< orphan*/  breathing_enable () ; 
 int encoder_mode ; 
 TYPE_1__ kb_backlight_config ; 
 int /*<<< orphan*/  retrieve_custom_encoder_config (int,int /*<<< orphan*/ ) ; 
 int time_config_idx ; 

uint16_t handle_encoder_press(){
  uint16_t mapped_code = 0;
  switch(encoder_mode){
    case ENC_MODE_VOLUME:
      mapped_code = KC_MUTE;
      break;
    default:
    case ENC_MODE_MEDIA:
      mapped_code = KC_MEDIA_PLAY_PAUSE;
      break;
    case ENC_MODE_SCROLL:
      mapped_code = KC_BTN3;
      break;
    case ENC_MODE_BACKLIGHT:
      // mapped_code = BL_TOGG;
      kb_backlight_config.breathing = !kb_backlight_config.breathing;
      if(!kb_backlight_config.breathing){
        breathing_disable();
      } else{
        breathing_enable();
      }
      break;
#ifdef DYNAMIC_KEYMAP_ENABLE
    case ENC_MODE_CUSTOM0:
      mapped_code = retrieve_custom_encoder_config(0, ENC_CUSTOM_PRESS);
      break;
    case ENC_MODE_CUSTOM1:
      mapped_code = retrieve_custom_encoder_config(1, ENC_CUSTOM_PRESS);
      break;
    case ENC_MODE_CUSTOM2:
      mapped_code = retrieve_custom_encoder_config(2, ENC_CUSTOM_PRESS);
      break;
#endif
    case ENC_MODE_CLOCK_SET:
      time_config_idx = (time_config_idx + 1) % 5;
    case ENC_MODE_BRIGHTNESS:
      break;
  }
  return mapped_code;
}