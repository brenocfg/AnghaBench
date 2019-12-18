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
 int /*<<< orphan*/  isLeftHand ; 
 int /*<<< orphan*/  is_keyboard_left () ; 
 scalar_t__ is_keyboard_master () ; 
 int /*<<< orphan*/  keyboard_master_setup () ; 
 int /*<<< orphan*/  keyboard_slave_setup () ; 

void matrix_setup(void)
{
  isLeftHand = is_keyboard_left();

  if (is_keyboard_master())
  {
    keyboard_master_setup();
  }
  else
  {
    keyboard_slave_setup();
  }
}