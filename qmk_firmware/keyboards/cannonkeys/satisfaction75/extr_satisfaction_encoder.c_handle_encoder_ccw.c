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
struct TYPE_2__ {int enable; int /*<<< orphan*/  level; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENC_CUSTOM_CCW ; 
#define  ENC_MODE_BACKLIGHT 136 
#define  ENC_MODE_BRIGHTNESS 135 
#define  ENC_MODE_CLOCK_SET 134 
#define  ENC_MODE_CUSTOM0 133 
#define  ENC_MODE_CUSTOM1 132 
#define  ENC_MODE_CUSTOM2 131 
#define  ENC_MODE_MEDIA 130 
#define  ENC_MODE_SCROLL 129 
#define  ENC_MODE_VOLUME 128 
 int /*<<< orphan*/  KC_BRIGHTNESS_DOWN ; 
 int /*<<< orphan*/  KC_MEDIA_PREV_TRACK ; 
 int /*<<< orphan*/  KC_VOLD ; 
 int /*<<< orphan*/  KC_WH_U ; 
 int /*<<< orphan*/  backlight_set (int /*<<< orphan*/ ) ; 
 int encoder_mode ; 
 TYPE_1__ kb_backlight_config ; 
 int queue_for_send ; 
 int /*<<< orphan*/  retrieve_custom_encoder_config (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_time_config (int) ; 

uint16_t handle_encoder_ccw(){
  uint16_t mapped_code = 0;
  switch(encoder_mode){
    default:
    case ENC_MODE_VOLUME:
      mapped_code = KC_VOLD;
      break;
    case ENC_MODE_MEDIA:
      mapped_code = KC_MEDIA_PREV_TRACK;
      break;
    case ENC_MODE_SCROLL:
      mapped_code = KC_WH_U;
      break;
    case ENC_MODE_BACKLIGHT:
      // mapped_code = BL_DEC;
      if(kb_backlight_config.level != 0){
        kb_backlight_config.level = kb_backlight_config.level - 1;
      }
      backlight_set(kb_backlight_config.level);
      if (kb_backlight_config.level == 0){
        kb_backlight_config.enable = false;
      }
      break;
    case ENC_MODE_BRIGHTNESS:
      mapped_code = KC_BRIGHTNESS_DOWN;
      break;
#ifdef DYNAMIC_KEYMAP_ENABLE
    case ENC_MODE_CUSTOM0:
      mapped_code = retrieve_custom_encoder_config(0, ENC_CUSTOM_CCW);
      break;
    case ENC_MODE_CUSTOM1:
      mapped_code = retrieve_custom_encoder_config(1, ENC_CUSTOM_CCW);
      break;
    case ENC_MODE_CUSTOM2:
      mapped_code = retrieve_custom_encoder_config(2, ENC_CUSTOM_CCW);
      break;
#endif

    case ENC_MODE_CLOCK_SET:
      update_time_config(-1);
      queue_for_send = true;
      break;
  }
  return mapped_code;
}