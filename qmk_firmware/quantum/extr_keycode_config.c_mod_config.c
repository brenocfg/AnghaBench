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
typedef  int uint8_t ;
struct TYPE_2__ {scalar_t__ no_gui; scalar_t__ swap_rctl_rgui; scalar_t__ swap_lctl_lgui; scalar_t__ swap_ralt_rgui; scalar_t__ swap_lalt_lgui; } ;

/* Variables and functions */
 int MOD_LALT ; 
 int MOD_LCTL ; 
 int MOD_LGUI ; 
 int MOD_RALT ; 
 int MOD_RCTL ; 
 int MOD_RGUI ; 
 TYPE_1__ keymap_config ; 

uint8_t mod_config(uint8_t mod) {
    if (keymap_config.swap_lalt_lgui) {
        if ((mod & MOD_RGUI) == MOD_LGUI) {
            mod &= ~MOD_LGUI;
            mod |= MOD_LALT;
        } else if ((mod & MOD_RALT) == MOD_LALT) {
            mod &= ~MOD_LALT;
            mod |= MOD_LGUI;
        }
    }
    if (keymap_config.swap_ralt_rgui) {
        if ((mod & MOD_RGUI) == MOD_RGUI) {
            mod &= ~MOD_RGUI;
            mod |= MOD_RALT;
        } else if ((mod & MOD_RALT) == MOD_RALT) {
            mod &= ~MOD_RALT;
            mod |= MOD_RGUI;
        }
    }
    if (keymap_config.swap_lctl_lgui) {
        if ((mod & MOD_RGUI) == MOD_LGUI) {
            mod &= ~MOD_LGUI;
            mod |= MOD_LCTL;
        } else if ((mod & MOD_RCTL) == MOD_LCTL) {
            mod &= ~MOD_LCTL;
            mod |= MOD_LGUI;
        }
    }
    if (keymap_config.swap_rctl_rgui) {
        if ((mod & MOD_RGUI) == MOD_RGUI) {
            mod &= ~MOD_RGUI;
            mod |= MOD_RCTL;
        } else if ((mod & MOD_RCTL) == MOD_RCTL) {
            mod &= ~MOD_RCTL;
            mod |= MOD_RGUI;
        }
    }
    if (keymap_config.no_gui) {
        mod &= ~MOD_LGUI;
        mod &= ~MOD_RGUI;
    }

    return mod;
}