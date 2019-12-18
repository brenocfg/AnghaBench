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

/* Variables and functions */
 int /*<<< orphan*/  clear_superduper_key_combos () ; 
 int /*<<< orphan*/  set_superduper_key_combos () ; 
 int superduper_enabled ; 

bool toggle_superduper_mode(void) {
    superduper_enabled = !superduper_enabled;

    if (superduper_enabled) {
        set_superduper_key_combos();
    } else {
        clear_superduper_key_combos();
    }

    return superduper_enabled;
}