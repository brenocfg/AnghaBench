#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;
struct TYPE_7__ {int nkro; int /*<<< orphan*/  raw; } ;

/* Variables and functions */
#define  BACKLIT 136 
#define  COLEMAK 135 
#define  DP_OFF 134 
#define  DP_ON 133 
#define  DVORAK 132 
#define  EXT_PLV 131 
#define  KC_CAPS 130 
 int /*<<< orphan*/  KC_RSFT ; 
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
#define  PLOVER 129 
 int PORTE ; 
#define  QWERTY 128 
 int USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  _ADJUST ; 
 int /*<<< orphan*/  _COLEMAK ; 
 int /*<<< orphan*/  _DPAD ; 
 int /*<<< orphan*/  _DVORAK ; 
 int /*<<< orphan*/  _FN1 ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _PLOVER ; 
 int /*<<< orphan*/  _QWERTY ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  backlight_step () ; 
 int /*<<< orphan*/  caps_song_off ; 
 int /*<<< orphan*/  caps_song_on ; 
 int /*<<< orphan*/  dpad_song_off ; 
 int /*<<< orphan*/  dpad_song_on ; 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  eeconfig_is_enabled () ; 
 int /*<<< orphan*/  eeconfig_read_keymap () ; 
 int /*<<< orphan*/  eeconfig_update_keymap (int /*<<< orphan*/ ) ; 
 int host_keyboard_leds () ; 
 TYPE_4__ keymap_config ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plover_gb_song ; 
 int /*<<< orphan*/  plover_song ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_all_notes () ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
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
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          PORTE &= ~(1<<6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          PORTE |= (1<<6);
        #endif
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;
	  
	  
// Play audio upon switching Caps Lock and custom layers

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
		return true;
		
	case DP_ON:
		if (record->event.pressed) {
			
		} else {
			#ifdef AUDIO_ENABLE
			PLAY_SONG(dpad_song_on);
			#endif
			
			layer_off(_FN1);
			layer_on(_DPAD);
		}
		
	case DP_OFF:
		if (record->event.pressed) {
			#ifdef AUDIO_ENABLE	
			PLAY_SONG(dpad_song_off);
			#endif
			
			layer_off(_DPAD);	
		}
    }
  return true;
}