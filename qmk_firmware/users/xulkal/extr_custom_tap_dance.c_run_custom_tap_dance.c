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
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t KC_TRANSPARENT ; 
 scalar_t__ TAPPING_TERM ; 
 size_t TD_MIN ; 
 int /*<<< orphan*/  pgm_read_word (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tap_code16 (int /*<<< orphan*/ ) ; 
 size_t td_keycode ; 
 int /*<<< orphan*/ ** td_keymaps ; 
 scalar_t__ td_timer ; 
 scalar_t__ timer_read () ; 

__attribute__((used)) static void run_custom_tap_dance(uint8_t i)
{
    tap_code16(pgm_read_word(&td_keymaps[td_keycode - TD_MIN][i]));
    td_keycode = KC_TRANSPARENT;
    td_timer = timer_read() + TAPPING_TERM;
}