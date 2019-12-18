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
 scalar_t__ QWERTY ; 
 scalar_t__ REP_DELAY ; 
 scalar_t__ REP_INIT_DELAY ; 
 scalar_t__ cMode ; 
 int /*<<< orphan*/  clear_keyboard () ; 
 int /*<<< orphan*/  inChord ; 
 int /*<<< orphan*/  processChord (int) ; 
 int repEngaged ; 
 int /*<<< orphan*/  repTimer ; 
 int /*<<< orphan*/  send_keyboard_report () ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 

void matrix_scan_user(void) {
	// We abuse this for early sending of key
	// Key repeat only on QWER/SYMB layers
	if (cMode != QWERTY || !inChord) return;

	// Check timers
#ifndef NO_REPEAT
	if (repEngaged && timer_elapsed(repTimer) > REP_DELAY) {
		// Process Key for report
		processChord(false);

		// Send report to host
		send_keyboard_report();
		clear_keyboard();
		repTimer = timer_read();
	}

	if (!repEngaged && timer_elapsed(repTimer) > REP_INIT_DELAY) {
		repEngaged = true;
	}
#endif
}