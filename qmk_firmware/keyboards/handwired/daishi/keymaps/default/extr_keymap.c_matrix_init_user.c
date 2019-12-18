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
 int /*<<< orphan*/  C4 ; 
 int /*<<< orphan*/  C5 ; 
 int /*<<< orphan*/  C6 ; 
 int /*<<< orphan*/  setPinOutput (int /*<<< orphan*/ ) ; 

void matrix_init_user(void) {
  // Call the keymap level matrix init.

  // Set our LED pins as output
  setPinOutput(C4);
  setPinOutput(C5);
  setPinOutput(C6);
}