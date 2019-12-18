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
struct TYPE_4__ {scalar_t__ pressed; } ;
struct TYPE_5__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 int DOWN ; 
 int /*<<< orphan*/  END ; 
 int /*<<< orphan*/  LCTL ; 
 int LEFT ; 
 int /*<<< orphan*/  LGUI ; 
 int /*<<< orphan*/  LSFT ; 
 int /*<<< orphan*/  const* MACRO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  const* MACRO_NONE ; 
 int RGHT ; 
 int SPC ; 
 int /*<<< orphan*/  T (int) ; 
 int /*<<< orphan*/  U (int /*<<< orphan*/ ) ; 
 int UP ; 
 int /*<<< orphan*/  rgblight_setrgb (int,int,int) ; 

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    if (record->event.pressed) {
        switch(id) {
            case 0:
                return MACRO(D(LGUI), D(LSFT), T(3), U(LSFT), U(LGUI), END);                   // Mac print screen
            case 1:
                return MACRO(D(LGUI), D(LSFT), T(4), U(LSFT), U(LGUI), END);                   // Mac print area
            case 2:
                return MACRO(D(LCTL), D(LSFT), D(LGUI), T(3), D(LCTL), D(LSFT), D(LGUI), END); // Mac print screen to clipboard
            case 3:
                return MACRO(D(LCTL), D(LSFT), D(LGUI), T(4), D(LCTL), D(LSFT), D(LGUI), END); // Mac print area to clipboard
            case 4:
                return MACRO(D(LCTL), T(UP), U(LCTL), END);                                    // Mac mission control
            case 5:
                return MACRO(D(LCTL), T(DOWN), U(LCTL), END);                                  // Mac app windows
            case 6:
                return MACRO(D(LGUI), T(SPC), U(LGUI), END);                                   // Mac spotlight search
            case 7:
                return MACRO(D(LCTL), T(LEFT), U(LCTL), END);                                  // Mac mission left
            case 8:
                return MACRO(D(LCTL), T(RGHT), U(LCTL), END);                                  // Mac mission right
            case 9:
                rgblight_setrgb(0xff, 0xff, 0xff);                                             // White rgb shortcut
                break;
        }
    }
    return MACRO_NONE;
}