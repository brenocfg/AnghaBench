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
typedef  int uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  swap_backslash_backspace; int /*<<< orphan*/  swap_grave_esc; int /*<<< orphan*/  no_gui; int /*<<< orphan*/  swap_rctl_rgui; int /*<<< orphan*/  swap_ralt_rgui; int /*<<< orphan*/  swap_lctl_lgui; int /*<<< orphan*/  swap_lalt_lgui; int /*<<< orphan*/  swap_control_capslock; int /*<<< orphan*/  capslock_to_control; } ;

/* Variables and functions */
#define  KC_BSLASH 139 
#define  KC_BSPACE 138 
#define  KC_CAPSLOCK 137 
#define  KC_ESC 136 
#define  KC_GRAVE 135 
#define  KC_LALT 134 
#define  KC_LCTL 133 
 int KC_LCTRL ; 
#define  KC_LGUI 132 
#define  KC_LOCKING_CAPS 131 
 int KC_NO ; 
#define  KC_RALT 130 
#define  KC_RCTL 129 
#define  KC_RGUI 128 
 TYPE_1__ keymap_config ; 

uint16_t keycode_config(uint16_t keycode) {
    switch (keycode) {
        case KC_CAPSLOCK:
        case KC_LOCKING_CAPS:
            if (keymap_config.swap_control_capslock || keymap_config.capslock_to_control) {
                return KC_LCTL;
            }
            return keycode;
        case KC_LCTL:
            if (keymap_config.swap_control_capslock) {
                return KC_CAPSLOCK;
            }
            if (keymap_config.swap_lctl_lgui) {
                if (keymap_config.no_gui) {
                    return KC_NO;
                }
                return KC_LGUI;
            }
            return KC_LCTL;
        case KC_LALT:
            if (keymap_config.swap_lalt_lgui) {
                if (keymap_config.no_gui) {
                    return KC_NO;
                }
                return KC_LGUI;
            }
            return KC_LALT;
        case KC_LGUI:
            if (keymap_config.swap_lalt_lgui) {
                return KC_LALT;
            }
            if (keymap_config.swap_lctl_lgui) {
                return KC_LCTRL;
            }
            if (keymap_config.no_gui) {
                return KC_NO;
            }
            return KC_LGUI;
        case KC_RCTL:
            if (keymap_config.swap_rctl_rgui) {
                if (keymap_config.no_gui) {
                    return KC_NO;
                }
                return KC_RGUI;
            }
            return KC_RCTL;
        case KC_RALT:
            if (keymap_config.swap_ralt_rgui) {
                if (keymap_config.no_gui) {
                    return KC_NO;
                }
                return KC_RGUI;
            }
            return KC_RALT;
        case KC_RGUI:
            if (keymap_config.swap_ralt_rgui) {
                return KC_RALT;
            }
            if (keymap_config.swap_rctl_rgui) {
                return KC_RCTL;
            }
            if (keymap_config.no_gui) {
                return KC_NO;
            }
            return KC_RGUI;
        case KC_GRAVE:
            if (keymap_config.swap_grave_esc) {
                return KC_ESC;
            }
            return KC_GRAVE;
        case KC_ESC:
            if (keymap_config.swap_grave_esc) {
                return KC_GRAVE;
            }
            return KC_ESC;
        case KC_BSLASH:
            if (keymap_config.swap_backslash_backspace) {
                return KC_BSPACE;
            }
            return KC_BSLASH;
        case KC_BSPACE:
            if (keymap_config.swap_backslash_backspace) {
                return KC_BSLASH;
            }
            return KC_BSPACE;
        default:
            return keycode;
    }
}