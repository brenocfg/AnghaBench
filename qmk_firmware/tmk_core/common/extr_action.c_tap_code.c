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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ KC_CAPS ; 
 int /*<<< orphan*/  TAP_CODE_DELAY ; 
 int /*<<< orphan*/  TAP_HOLD_CAPS_DELAY ; 
 int /*<<< orphan*/  register_code (scalar_t__) ; 
 int /*<<< orphan*/  unregister_code (scalar_t__) ; 
 int /*<<< orphan*/  wait_ms (int /*<<< orphan*/ ) ; 

void tap_code(uint8_t code) {
    register_code(code);
    if (code == KC_CAPS) {
        wait_ms(TAP_HOLD_CAPS_DELAY);
    } else {
        wait_ms(TAP_CODE_DELAY);
    }
    unregister_code(code);
}