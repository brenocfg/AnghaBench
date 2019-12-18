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
typedef  int /*<<< orphan*/  qk_tap_dance_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  diablo_tapdance_master (int /*<<< orphan*/ *,void*,int) ; 

void diablo_tapdance2(qk_tap_dance_state_t *state, void *user_data) { diablo_tapdance_master(state, user_data, 1); }