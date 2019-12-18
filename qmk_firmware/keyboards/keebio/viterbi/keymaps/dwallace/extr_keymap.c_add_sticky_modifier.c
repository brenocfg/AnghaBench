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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_mods (int /*<<< orphan*/ ) ; 
 int modifier_already_applied ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 

void add_sticky_modifier(uint16_t keycode) {
  add_mods(MOD_BIT(keycode));
  register_code(keycode);
  modifier_already_applied = false;
}