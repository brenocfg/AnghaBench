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
 int /*<<< orphan*/  CAPSLOCKLEDPIN ; 
 int /*<<< orphan*/  NUMLOCKLEDPIN ; 
 int /*<<< orphan*/  SCROLLLOCKLEDPIN ; 
 int /*<<< orphan*/  dynamic_macro_init () ; 
 int /*<<< orphan*/  setPinOutput (int /*<<< orphan*/ ) ; 

void keyboard_pre_init_user(void) {
  /* Configure LED driving pins as output pins */
  setPinOutput(NUMLOCKLEDPIN);
  setPinOutput(CAPSLOCKLEDPIN);
  setPinOutput(SCROLLLOCKLEDPIN);

  dynamic_macro_init();
}