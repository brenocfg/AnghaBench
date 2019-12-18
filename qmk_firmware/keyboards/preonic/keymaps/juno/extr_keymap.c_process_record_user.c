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
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
#define  BACKLIT 136 
#define  COLEMAK 135 
#define  DP_OFF 134 
#define  DP_ON 133 
#define  DVORAK 132 
#define  KC_CAPS 131 
 int /*<<< orphan*/  KC_RSFT ; 
#define  LOWER 130 
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
 int PORTE ; 
#define  QWERTY 129 
#define  RAISE 128 
 int USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  _ADJUST ; 
 int /*<<< orphan*/  _COLEMAK ; 
 int /*<<< orphan*/  _DPAD ; 
 int /*<<< orphan*/  _DVORAK ; 
 int /*<<< orphan*/  _FN1 ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _QWERTY ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  backlight_step () ; 
 int /*<<< orphan*/  caps_song_off ; 
 int /*<<< orphan*/  caps_song_on ; 
 int /*<<< orphan*/  dpad_song_off ; 
 int /*<<< orphan*/  dpad_song_on ; 
 int host_keyboard_leds () ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_DVORAK);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            PORTE &= ~(1<<6);
          } else {
            unregister_code(KC_RSFT);
            PORTE |= (1<<6);
          }
          return false;
          break;
		 
		 
		 
		// Additional personal custom functions	  

		case KC_CAPS:
			if (record->event.pressed) {
				#ifdef AUDIO_ENABLE
				if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
					PLAY_SONG(caps_song_off);
				} else {
					PLAY_SONG(caps_song_on);
				}
				#endif
			}
			return true; // process the actual function of Caps Lock
			//break;
			
		case DP_ON:
			if (record->event.pressed) {
				
			} else {
				// activated upon release
				#ifdef AUDIO_ENABLE
				PLAY_SONG(dpad_song_on);
				#endif
				
				layer_off(_FN1);
				layer_on(_DPAD);
			}
			
		case DP_OFF:
			if (record->event.pressed) {
				// deactivated upon pressdown
				#ifdef AUDIO_ENABLE	
				PLAY_SONG(dpad_song_off);
				#endif
				
				//layer_off(_FN1); // do not put in this line
				layer_off(_DPAD);	
			}
		 
      }
    return true;
}