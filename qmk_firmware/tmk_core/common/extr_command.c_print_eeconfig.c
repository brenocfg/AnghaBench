#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  nkro; int /*<<< orphan*/  swap_backslash_backspace; int /*<<< orphan*/  swap_grave_esc; int /*<<< orphan*/  no_gui; int /*<<< orphan*/  swap_ralt_rgui; int /*<<< orphan*/  swap_lalt_lgui; int /*<<< orphan*/  swap_rctl_rgui; int /*<<< orphan*/  swap_lctl_lgui; int /*<<< orphan*/  capslock_to_control; int /*<<< orphan*/  swap_control_capslock; int /*<<< orphan*/  raw; } ;
typedef  TYPE_1__ keymap_config_t ;
struct TYPE_5__ {int /*<<< orphan*/  mouse; int /*<<< orphan*/  keyboard; int /*<<< orphan*/  matrix; int /*<<< orphan*/  enable; int /*<<< orphan*/  raw; } ;
typedef  TYPE_2__ debug_config_t ;
struct TYPE_6__ {int /*<<< orphan*/  level; int /*<<< orphan*/  enable; int /*<<< orphan*/  raw; } ;
typedef  TYPE_3__ backlight_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  eeconfig_read_backlight () ; 
 int /*<<< orphan*/  eeconfig_read_debug () ; 
 int /*<<< orphan*/  eeconfig_read_default_layer () ; 
 int /*<<< orphan*/  eeconfig_read_keymap () ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  print_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex8 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_eeconfig(void) {
// Print these variables if NO_PRINT or USER_PRINT are not defined.
#if !defined(NO_PRINT) && !defined(USER_PRINT)

    print("default_layer: ");
    print_dec(eeconfig_read_default_layer());
    print("\n");

    debug_config_t dc;
    dc.raw = eeconfig_read_debug();
    print("debug_config.raw: ");
    print_hex8(dc.raw);
    print("\n");
    print(".enable: ");
    print_dec(dc.enable);
    print("\n");
    print(".matrix: ");
    print_dec(dc.matrix);
    print("\n");
    print(".keyboard: ");
    print_dec(dc.keyboard);
    print("\n");
    print(".mouse: ");
    print_dec(dc.mouse);
    print("\n");

    keymap_config_t kc;
    kc.raw = eeconfig_read_keymap();
    print("keymap_config.raw: ");
    print_hex8(kc.raw);
    print("\n");
    print(".swap_control_capslock: ");
    print_dec(kc.swap_control_capslock);
    print("\n");
    print(".capslock_to_control: ");
    print_dec(kc.capslock_to_control);
    print("\n");
    print(".swap_lctl_lgui: ");
    print_dec(kc.swap_lctl_lgui);
    print("\n");
    print(".swap_rctl_rgui: ");
    print_dec(kc.swap_rctl_rgui);
    print("\n");
    print(".swap_lalt_lgui: ");
    print_dec(kc.swap_lalt_lgui);
    print("\n");
    print(".swap_ralt_rgui: ");
    print_dec(kc.swap_ralt_rgui);
    print("\n");
    print(".no_gui: ");
    print_dec(kc.no_gui);
    print("\n");
    print(".swap_grave_esc: ");
    print_dec(kc.swap_grave_esc);
    print("\n");
    print(".swap_backslash_backspace: ");
    print_dec(kc.swap_backslash_backspace);
    print("\n");
    print(".nkro: ");
    print_dec(kc.nkro);
    print("\n");

#    ifdef BACKLIGHT_ENABLE
    backlight_config_t bc;
    bc.raw = eeconfig_read_backlight();
    print("backlight_config.raw: ");
    print_hex8(bc.raw);
    print("\n");
    print(".enable: ");
    print_dec(bc.enable);
    print("\n");
    print(".level: ");
    print_dec(bc.level);
    print("\n");
#    endif /* BACKLIGHT_ENABLE */

#endif /* !NO_PRINT */
}