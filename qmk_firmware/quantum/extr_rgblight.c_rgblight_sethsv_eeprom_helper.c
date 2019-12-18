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
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_7__ {size_t mode; int val; int hue; int sat; int /*<<< orphan*/  raw; scalar_t__ enable; } ;
struct TYPE_6__ {scalar_t__ base_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  TYPE_1__ LED_TYPE ;

/* Variables and functions */
 int* RGBLED_GRADIENT_RANGES ; 
 scalar_t__ RGBLIGHT_MODE_BREATHING ; 
 scalar_t__ RGBLIGHT_MODE_RAINBOW_MOOD ; 
 scalar_t__ RGBLIGHT_MODE_RAINBOW_SWIRL ; 
 scalar_t__ RGBLIGHT_MODE_STATIC_GRADIENT ; 
 size_t RGBLIGHT_MODE_STATIC_LIGHT ; 
 int /*<<< orphan*/  RGBLIGHT_SPLIT_SET_CHANGE_HSVS ; 
 int /*<<< orphan*/  dprintf (char*,int,int,int,...) ; 
 int /*<<< orphan*/  eeconfig_update_rgblight (int /*<<< orphan*/ ) ; 
 int effect_num_leds ; 
 int effect_start_pos ; 
 int /*<<< orphan*/ * led ; 
 scalar_t__* mode_base_table ; 
 int pgm_read_word (int*) ; 
 TYPE_4__ rgblight_config ; 
 int /*<<< orphan*/  rgblight_set () ; 
 int /*<<< orphan*/  rgblight_setrgb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ rgblight_status ; 
 int /*<<< orphan*/  sethsv (int,int,int,TYPE_1__*) ; 

void rgblight_sethsv_eeprom_helper(uint8_t hue, uint8_t sat, uint8_t val, bool write_to_eeprom) {
    if (rgblight_config.enable) {
        rgblight_status.base_mode = mode_base_table[rgblight_config.mode];
        if (rgblight_config.mode == RGBLIGHT_MODE_STATIC_LIGHT) {
            // same static color
            LED_TYPE tmp_led;
            sethsv(hue, sat, val, &tmp_led);
            rgblight_setrgb(tmp_led.r, tmp_led.g, tmp_led.b);
        } else {
            // all LEDs in same color
            if (1 == 0) {  // dummy
            }
#ifdef RGBLIGHT_EFFECT_BREATHING
            else if (rgblight_status.base_mode == RGBLIGHT_MODE_BREATHING) {
                // breathing mode, ignore the change of val, use in memory value instead
                val = rgblight_config.val;
            }
#endif
#ifdef RGBLIGHT_EFFECT_RAINBOW_MOOD
            else if (rgblight_status.base_mode == RGBLIGHT_MODE_RAINBOW_MOOD) {
                // rainbow mood, ignore the change of hue
                hue = rgblight_config.hue;
            }
#endif
#ifdef RGBLIGHT_EFFECT_RAINBOW_SWIRL
            else if (rgblight_status.base_mode == RGBLIGHT_MODE_RAINBOW_SWIRL) {
                // rainbow swirl, ignore the change of hue
                hue = rgblight_config.hue;
            }
#endif
#ifdef RGBLIGHT_EFFECT_STATIC_GRADIENT
            else if (rgblight_status.base_mode == RGBLIGHT_MODE_STATIC_GRADIENT) {
                // static gradient
                uint8_t delta     = rgblight_config.mode - rgblight_status.base_mode;
                bool    direction = (delta % 2) == 0;
#    ifdef __AVR__
                // probably due to how pgm_read_word is defined for ARM, but the ARM compiler really hates this line
                uint8_t range = pgm_read_word(&RGBLED_GRADIENT_RANGES[delta / 2]);
#    else
                uint8_t range = RGBLED_GRADIENT_RANGES[delta / 2];
#    endif
                for (uint8_t i = 0; i < effect_num_leds; i++) {
                    uint8_t _hue = ((uint16_t)i * (uint16_t)range) / effect_num_leds;
                    if (direction) {
                        _hue = hue + _hue;
                    } else {
                        _hue = hue - _hue;
                    }
                    dprintf("rgblight rainbow set hsv: %d,%d,%d,%u\n", i, _hue, direction, range);
                    sethsv(_hue, sat, val, (LED_TYPE *)&led[i + effect_start_pos]);
                }
                rgblight_set();
            }
#endif
        }
#ifdef RGBLIGHT_SPLIT
        if (rgblight_config.hue != hue || rgblight_config.sat != sat || rgblight_config.val != val) {
            RGBLIGHT_SPLIT_SET_CHANGE_HSVS;
        }
#endif
        rgblight_config.hue = hue;
        rgblight_config.sat = sat;
        rgblight_config.val = val;
        if (write_to_eeprom) {
            eeconfig_update_rgblight(rgblight_config.raw);
            dprintf("rgblight set hsv [EEPROM]: %u,%u,%u\n", rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
        } else {
            dprintf("rgblight set hsv [NOEEPROM]: %u,%u,%u\n", rgblight_config.hue, rgblight_config.sat, rgblight_config.val);
        }
    }
}