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
 int /*<<< orphan*/  KC_ENT ; 
 int /*<<< orphan*/  KC_UP ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmux_pane_last () ; 

void tmux_pane_switch_repeat(void) {
  tmux_pane_last();
  tap_code(KC_UP);
  tap_code(KC_ENT);
  tmux_pane_last();
}