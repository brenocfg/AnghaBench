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
 int /*<<< orphan*/  matrix_init_user () ; 
 int /*<<< orphan*/  set_all_leds_to (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void matrix_init_kb(void) {
  /* the bootloader can leave LEDs on, so */
  set_all_leds_to(0, 0, 0);
  matrix_init_user();
}