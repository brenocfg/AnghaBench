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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ SINGLE_TAP ; 
 scalar_t__ TD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TD_SYM_VIM ; 
 int tap_dance_active ; 
 scalar_t__ tap_dance_state ; 

void tap_dance_process_keycode(uint16_t keycode) {
    if (tap_dance_state == SINGLE_TAP && keycode != TD(TD_SYM_VIM)) {
        tap_dance_active = false;
    }
}