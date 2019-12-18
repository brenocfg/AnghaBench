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
 int /*<<< orphan*/  KC_ALGR ; 
 int /*<<< orphan*/  _FX ; 
 int /*<<< orphan*/  _NR ; 
 int /*<<< orphan*/  _NR_L3 ; 
 scalar_t__ layer_state_is (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tri_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void update_tri_layer_user(void) {
    update_tri_layer(_NR, _NR_L3, _FX);
    if (layer_state_is(_NR_L3) && !layer_state_is(_FX)) {
        register_code(KC_ALGR);
    } else {
        unregister_code(KC_ALGR);
    }
}