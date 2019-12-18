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
typedef  int uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int DYN_REC_STOP ; 
 int /*<<< orphan*/  KC_POWER ; 
 int /*<<< orphan*/  KC_RCTL ; 
 int /*<<< orphan*/  KC_RSFT ; 
#define  MACSLEEP 130 
 int MO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLAY_NOTE_ARRAY (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
#define  USEFNMODS 129 
#define  USENUMMODS 128 
 int /*<<< orphan*/  _ADJUST ; 
 unsigned long _QWERTY ; 
 unsigned long _QWERTYNUMMODS ; 
 int /*<<< orphan*/  persistent_default_layer_set (unsigned long) ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  println (char*) ; 
 int /*<<< orphan*/  process_record_dynamic_macro (int,TYPE_2__*) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int singular_key ; 
 int /*<<< orphan*/  tone_fnmac ; 
 int /*<<< orphan*/  tone_fnpc ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    uint16_t macro_kc = (keycode == MO(_ADJUST) ? DYN_REC_STOP : keycode);
    if (!process_record_dynamic_macro(macro_kc, record))
    {
        return false;
    }
    println(" ");
    print("process record");

    switch (keycode)
    {
    case MACSLEEP:
        if (record->event.pressed)
        {
            // ACTION_MODS_KEY(MOD_LCTL | MOD_LSFT, KC_POWER);
            register_code(KC_RSFT);
            register_code(KC_RCTL);
            register_code(KC_POWER);
            unregister_code(KC_POWER);
            unregister_code(KC_RCTL);
            unregister_code(KC_RSFT);
        }
        return false;
        break;
    case USEFNMODS:
        if (record->event.pressed)
        {
            persistent_default_layer_set(1UL << _QWERTY);
#ifdef AUDIO_ENABLE
            PLAY_NOTE_ARRAY(tone_fnpc, false, 0);
#endif
            print("Space-FN");
        }
        return false;
        break;
    case USENUMMODS:
        if (record->event.pressed)
        {
            persistent_default_layer_set(1UL << _QWERTYNUMMODS);
#ifdef AUDIO_ENABLE
            PLAY_NOTE_ARRAY(tone_fnmac, false, 0);
#endif
            print("Space-Numpad");
        }
        return false;
        break;
    default:
        singular_key = false;
        break;
    }

    return true;
}