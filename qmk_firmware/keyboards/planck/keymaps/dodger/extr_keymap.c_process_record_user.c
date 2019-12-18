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
#define  CABBAGE 143 
#define  COLEMAK 142 
#define  COMMENTHEAD 141 
#define  DISNEY 140 
#define  DOOM 139 
#define  GCTOGG 138 
#define  LENNY 137 
#define  LOWER 136 
#define  MARIO 135 
#define  MARIOE 134 
#define  MCTOGG 133 
#define  NUMBERONE 132 
#define  OLDSPICE 131 
#define  OVERWATCH 130 
 int /*<<< orphan*/  PLAY_SONG (int /*<<< orphan*/ ) ; 
#define  RAISE 129 
#define  RICKANDMORT 128 
 int /*<<< orphan*/  SEND_STRING (char*) ; 
 int /*<<< orphan*/  _ADJUST ; 
 int /*<<< orphan*/  _COLEMAK ; 
 int /*<<< orphan*/  _GAME ; 
 int /*<<< orphan*/  _LOWER ; 
 int /*<<< orphan*/  _MUSIC ; 
 int /*<<< orphan*/  _RAISE ; 
 int /*<<< orphan*/  backlight_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cabbage ; 
 int /*<<< orphan*/  disney ; 
 int /*<<< orphan*/  doom ; 
 int isGame ; 
 int isMusic ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mario ; 
 int /*<<< orphan*/  marioe ; 
 int /*<<< orphan*/  numberone ; 
 int /*<<< orphan*/  oldspice ; 
 int /*<<< orphan*/  overwatch ; 
 int /*<<< orphan*/  setLayer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_single_persistent_default_layer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
        #ifdef BACKLIGHT_ENABLE
		  backlight_set(0);
        #endif
      }
      return false;
      break;
	case GCTOGG:
      if (record->event.pressed) {
		  if (isGame) {
              if (isMusic)
                  setLayer(_MUSIC);
              else
                  setLayer(_COLEMAK);
              isGame = false;
          } else {
              setLayer(_GAME);
              isGame = true;
          }
      }
      return false;
      break;
    case MCTOGG:
        if (record->event.pressed) {
            if (isMusic) {
                if (isGame)
                    setLayer(_GAME);
                else
                    setLayer(_COLEMAK);
                isMusic = false;
            } else {
                setLayer(_MUSIC);
                isMusic = true;
            }
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
    case LENNY:
    	if (record->event.pressed) {
    		SEND_STRING("()");
    	}
    	return false; break;
    case COMMENTHEAD:
    	if (record->event.pressed) {
    		SEND_STRING("// ---------------------------------------------------------------");
    	}
    	return false; break;
    case RICKANDMORT:
    	if (record->event.pressed) {
    		SEND_STRING("// ***************************************************************");
    	}
    	return false; break;
    case MARIO:
        if(record->event.pressed) {
          #ifdef AUDIO_ENABLE
            PLAY_SONG(mario);
          #endif
        }
        return false; break;
      case MARIOE:
          if(record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(marioe);
            #endif
          }
          return false; break;
      case OVERWATCH:
          if(record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(overwatch);
            #endif
          }
          return false; break;
      case DOOM:
          if(record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(doom);
            #endif
          }
          return false; break;
      case DISNEY:
          if(record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(disney);
            #endif
          }
          return false; break;
      case NUMBERONE:
          if(record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(numberone);
            #endif
          }
          return false; break;
      case CABBAGE:
          if(record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(cabbage);
            #endif
          }
          return false; break;
      case OLDSPICE:
          if(record->event.pressed) {
            #ifdef AUDIO_ENABLE
              PLAY_SONG(oldspice);
            #endif
          }
          return false; break;
  }
  return true;
}