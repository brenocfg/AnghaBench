#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int KC_LALT ; 
 int KC_LCTL ; 
 int KC_LGUI ; 
 int KC_LSFT ; 
 int KC_RALT ; 
 int KC_RCTL ; 
 int KC_RGUI ; 
 int KC_RSFT ; 
#define  MOD_LALT 135 
#define  MOD_LCTL 134 
#define  MOD_LGUI 133 
#define  MOD_LSFT 132 
#define  MOD_RALT 131 
#define  MOD_RCTL 130 
#define  MOD_RGUI 129 
#define  MOD_RSFT 128 
 int mod_config (int) ; 

uint16_t get_mod_kc(uint16_t keycode) {
    uint8_t mod = mod_config((keycode >> 0x8) & 0x1F);
    switch (mod) {
    case MOD_LCTL:
        return KC_LCTL;
    case MOD_RCTL:
        return KC_RCTL;
    case MOD_LSFT:
        return KC_LSFT;
    case MOD_RSFT:
        return KC_RSFT;
    case MOD_LALT:
        return KC_LALT;
    case MOD_RALT:
        return KC_RALT;
    case MOD_LGUI:
        return KC_LGUI;
    case MOD_RGUI:
        return KC_RGUI;
    default:
        // shrug?  this shouldn't happen.
        return keycode;
    }
}