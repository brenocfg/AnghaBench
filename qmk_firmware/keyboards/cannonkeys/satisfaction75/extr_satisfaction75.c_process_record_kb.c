#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_5__ {scalar_t__ pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  CLOCK_SET 130 
 int /*<<< orphan*/  ENC_MODE_CLOCK_SET ; 
#define  ENC_PRESS 129 
 int MACRO00 ; 
 int MACRO15 ; 
 int /*<<< orphan*/  MEDIA_KEY_DELAY ; 
#define  OLED_TOGG 128 
 int _NUM_OLED_MODES ; 
 int clock_set_mode ; 
 int /*<<< orphan*/  draw_ui () ; 
 int /*<<< orphan*/  dynamic_keymap_macro_send (int) ; 
 int /*<<< orphan*/  encoder_mode ; 
 int handle_encoder_press () ; 
 int oled_mode ; 
 int /*<<< orphan*/  post_encoder_mode_change () ; 
 int /*<<< orphan*/  pre_encoder_mode_change () ; 
 int /*<<< orphan*/  previous_encoder_mode ; 
 int process_record_user (int,TYPE_2__*) ; 
 int queue_for_send ; 
 int /*<<< orphan*/  register_code16 (int) ; 
 int /*<<< orphan*/  timer_elapsed (int) ; 
 int timer_read () ; 
 int /*<<< orphan*/  unregister_code16 (int) ; 

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  queue_for_send = true;
  switch (keycode) {
    case OLED_TOGG:
      if(!clock_set_mode){
        if (record->event.pressed) {
          oled_mode = (oled_mode + 1) % _NUM_OLED_MODES;
          draw_ui();
        }
      }
      return false;
    case CLOCK_SET:
      if (record->event.pressed) {
        if(clock_set_mode){
          pre_encoder_mode_change();
          clock_set_mode = false;
          encoder_mode = previous_encoder_mode;
          post_encoder_mode_change();

        }else{
          previous_encoder_mode = encoder_mode;
          pre_encoder_mode_change();
          clock_set_mode = true;
          encoder_mode = ENC_MODE_CLOCK_SET;
          post_encoder_mode_change();
        }
      }
      return false;
    case ENC_PRESS:
      if (record->event.pressed) {
        uint16_t mapped_code = handle_encoder_press();
        uint16_t held_keycode_timer = timer_read();
        if(mapped_code != 0){
          register_code16(mapped_code);
          while (timer_elapsed(held_keycode_timer) < MEDIA_KEY_DELAY){ /* no-op */ }
          unregister_code16(mapped_code);
        }
      } else {
        // Do something else when release
      }
      return false;
    default:
      break;
  }

#ifdef DYNAMIC_KEYMAP_ENABLE
	// Handle macros
	if (record->event.pressed) {
		if ( keycode >= MACRO00 && keycode <= MACRO15 )
		{
			uint8_t id = keycode - MACRO00;
			dynamic_keymap_macro_send(id);
			return false;
		}
	}
#endif //DYNAMIC_KEYMAP_ENABLE

  return process_record_user(keycode, record);
}