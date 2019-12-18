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
 int /*<<< orphan*/  KC_NO ; 
 int /*<<< orphan*/  VIM_LEADER (int /*<<< orphan*/ ) ; 
 int debug_enable ; 

void matrix_init_user(void) {
  debug_enable = true;
  VIM_LEADER(KC_NO);
}