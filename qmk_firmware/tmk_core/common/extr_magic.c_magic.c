#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  layer_state_t ;
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct TYPE_3__ {int /*<<< orphan*/  raw; } ;

/* Variables and functions */
 TYPE_2__ debug_config ; 
 int /*<<< orphan*/  default_layer_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eeconfig_init () ; 
 int /*<<< orphan*/  eeconfig_is_enabled () ; 
 int /*<<< orphan*/  eeconfig_read_debug () ; 
 scalar_t__ eeconfig_read_default_layer () ; 
 int /*<<< orphan*/  eeconfig_read_keymap () ; 
 TYPE_1__ keymap_config ; 

void magic(void) {
    /* check signature */
    if (!eeconfig_is_enabled()) {
        eeconfig_init();
    }

    /* debug enable */
    debug_config.raw = eeconfig_read_debug();

    /* keymap config */
    keymap_config.raw = eeconfig_read_keymap();

    uint8_t default_layer = 0;
    default_layer         = eeconfig_read_default_layer();
    default_layer_set((layer_state_t)default_layer);
}