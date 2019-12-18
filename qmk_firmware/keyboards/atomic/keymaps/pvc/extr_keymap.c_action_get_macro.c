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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  macro_t ;
struct TYPE_4__ {int /*<<< orphan*/  pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  LAYER_ADJUST ; 
 int /*<<< orphan*/  LAYER_FUNCTION ; 
 int /*<<< orphan*/  LAYER_LOWER ; 
 int /*<<< orphan*/  LAYER_MOUSE ; 
 unsigned long LAYER_QWERTY ; 
 int /*<<< orphan*/  LAYER_UPPER ; 
#define  MACRO_BACKLIGHT 153 
#define  MACRO_BREATH_DEFAULT 152 
#define  MACRO_BREATH_SPEED_DEC 151 
#define  MACRO_BREATH_SPEED_INC 150 
#define  MACRO_BREATH_TOGGLE 149 
#define  MACRO_FUNCTION 148 
#define  MACRO_HELP_1 147 
#define  MACRO_HELP_2 146 
#define  MACRO_HELP_3 145 
#define  MACRO_HELP_4 144 
#define  MACRO_HELP_5 143 
#define  MACRO_HELP_6 142 
#define  MACRO_HELP_7 141 
#define  MACRO_HELP_8 140 
#define  MACRO_HELP_9 139 
#define  MACRO_LOWER 138 
#define  MACRO_MOUSE 137 
 int /*<<< orphan*/  const* MACRO_NONE ; 
#define  MACRO_QWERTY 136 
#define  MACRO_TEMPO_D 135 
#define  MACRO_TEMPO_U 134 
#define  MACRO_TIMBRE_1 133 
#define  MACRO_TIMBRE_2 132 
#define  MACRO_TIMBRE_3 131 
#define  MACRO_TIMBRE_4 130 
#define  MACRO_TONE_DEFAULT 129 
#define  MACRO_UPPER 128 
 int /*<<< orphan*/  TEMPO_DEFAULT ; 
 int /*<<< orphan*/  TIMBRE_12 ; 
 int /*<<< orphan*/  TIMBRE_25 ; 
 int /*<<< orphan*/  TIMBRE_50 ; 
 int /*<<< orphan*/  TIMBRE_75 ; 
 int /*<<< orphan*/  TIMBRE_DEFAULT ; 
 int /*<<< orphan*/  backlight_step () ; 
 int /*<<< orphan*/  breathing_enable () ; 
 int /*<<< orphan*/  breathing_period_dec () ; 
 int /*<<< orphan*/  breathing_period_default () ; 
 int /*<<< orphan*/  breathing_period_inc () ; 
 int /*<<< orphan*/  breathing_period_set (int) ; 
 int /*<<< orphan*/  breathing_pulse () ; 
 int /*<<< orphan*/  breathing_self_disable () ; 
 int /*<<< orphan*/  breathing_toggle () ; 
 int /*<<< orphan*/  decrease_tempo (int) ; 
 int /*<<< orphan*/  increase_tempo (int) ; 
 int /*<<< orphan*/  layer_invert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  persistent_default_layer_set (unsigned long) ; 
 int /*<<< orphan*/  set_tempo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_timbre (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uprintf (char*) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

  // MACRODOWN only works in this function
  switch(id) {

        case MACRO_HELP_1:
            if (record->event.pressed)
            {
        uprintf("1");
            }
            break;

        case MACRO_HELP_2:
            if (record->event.pressed)
            {
        uprintf("2");
            }
            break;

        case MACRO_HELP_3:
            if (record->event.pressed)
            {
        uprintf("3");
            }
            break;

        case MACRO_HELP_4:
            if (record->event.pressed)
            {
        uprintf("4");
            }
            break;

        case MACRO_HELP_5:
            if (record->event.pressed)
            {
        uprintf("5");
            }
            break;

        case MACRO_HELP_6:
            if (record->event.pressed)
            {
        uprintf("6");
            }
            break;

        case MACRO_HELP_7:
            if (record->event.pressed)
            {
        uprintf("7");
            }
            break;

        case MACRO_HELP_8:
            if (record->event.pressed)
            {
        uprintf("8");
            }
            break;

        case MACRO_HELP_9:
            if (record->event.pressed)
            {
        uprintf("9");
            }
            break;

        case MACRO_BREATH_TOGGLE:
            if (record->event.pressed)
            {
                breathing_toggle();
            }
            break;

        case MACRO_BREATH_SPEED_INC:
            if (record->event.pressed)
            {
                breathing_period_inc();
            }
            break;

        case MACRO_BREATH_SPEED_DEC:
            if (record->event.pressed)
            {
                breathing_period_dec();
            }
            break;

        case MACRO_BREATH_DEFAULT:
            if (record->event.pressed)
            {
                breathing_period_default();
            }
            break;

        case MACRO_QWERTY:
            if (record->event.pressed)
            {
                persistent_default_layer_set(1UL<<LAYER_QWERTY);
            }
            break;

        case MACRO_UPPER:
            if (record->event.pressed)
            {
                layer_on(LAYER_UPPER);
                breathing_period_set(2);
                breathing_pulse();
                update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
            }
            else
            {
                layer_off(LAYER_UPPER);
                update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
            }
            break;

        case MACRO_LOWER:
            if (record->event.pressed)
            {
                layer_on(LAYER_LOWER);
                breathing_period_set(2);
                breathing_pulse();
                update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
            }
            else
            {
                layer_off(LAYER_LOWER);
                update_tri_layer(LAYER_LOWER, LAYER_UPPER, LAYER_ADJUST);
            }
            break;

        case MACRO_FUNCTION:
            if (record->event.pressed)
            {
                breathing_period_set(3);
                breathing_enable();
                layer_on(LAYER_FUNCTION);
            }
            else
            {
                breathing_period_set(1);
                breathing_self_disable();
                layer_off(LAYER_FUNCTION);
            }
            break;

#ifdef MOUSEKEY_ENABLE

        case MACRO_MOUSE:
            if (record->event.pressed)
            {
                layer_invert(LAYER_MOUSE);
            }
            break;

#endif /* MOUSEKEY_ENABLE */

#ifdef AUDIO_ENABLE

        case MACRO_TIMBRE_1:
            if (record->event.pressed) set_timbre(TIMBRE_12);
            break;

        case MACRO_TIMBRE_2:
            if (record->event.pressed) set_timbre(TIMBRE_25);
            break;

        case MACRO_TIMBRE_3:
            if (record->event.pressed) set_timbre(TIMBRE_50);
            break;

        case MACRO_TIMBRE_4:
            if (record->event.pressed) set_timbre(TIMBRE_75);
            break;

        case MACRO_TEMPO_U:
            if (record->event.pressed) increase_tempo(10);
            break;

        case MACRO_TEMPO_D:
            if (record->event.pressed) decrease_tempo(10);
            break;

        case MACRO_TONE_DEFAULT:
            if (record->event.pressed)
            {
                set_timbre(TIMBRE_DEFAULT);
                set_tempo(TEMPO_DEFAULT);
            }
            break;

/*
        case MACRO_AUDIO_TOGGLE:
            if (record->event.pressed)
            {
                    if (is_audio_on())
                    {
                        audio_off();
                    }
                    else
                    {
                        audio_on();
                        PLAY_SONG(tone_audio_on);
                    }
            }
            break;

        case MACRO_MUSIC_TOGGLE:
            if (record->event.pressed)
            {
                    if (IS_LAYER_ON(LAYER_MUSIC))
                    {
                        layer_off(LAYER_MUSIC);
                        stop_all_notes();
                    }
                    else
                    {
                    PLAY_SONG(tone_music_on);
                    layer_on(LAYER_MUSIC);
                    }
            }
            break;
        case MACRO_INC_VOICE:
            if (record->event.pressed)
            {
                #ifdef AUDIO_ENABLE
                    voice_iterate();
                    PLAY_SONG(music_scale);
                #endif
            }
            break;

        case MACRO_DEC_VOICE:
            if (record->event.pressed)
            {
                #ifdef AUDIO_ENABLE
                    voice_deiterate();
                    PLAY_SONG(music_scale);
                #endif
            }
            break;
*/

#endif /* AUDIO_ENABLE */

#ifdef BACKLIGHT_ENABLE
        case MACRO_BACKLIGHT:
            if (record->event.pressed)
            {
                backlight_step();
            }
#endif

        default:
            break;

    }
    return MACRO_NONE;
}