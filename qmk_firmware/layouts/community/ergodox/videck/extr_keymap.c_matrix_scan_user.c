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
 int /*<<< orphan*/  ARROWS ; 
 int /*<<< orphan*/  IS_LAYER_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOUSE ; 
 int /*<<< orphan*/  caps_lock_is_on ; 
 int /*<<< orphan*/  indicate_arrows_layer_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  indicate_caps_lock_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  indicate_mouse_layer_state (int /*<<< orphan*/ ) ; 

void matrix_scan_user(void) {
  // Check if we have shift locked.
  indicate_caps_lock_state(caps_lock_is_on);
  indicate_arrows_layer_state(IS_LAYER_ON(ARROWS));
  indicate_mouse_layer_state(IS_LAYER_ON(MOUSE));
}