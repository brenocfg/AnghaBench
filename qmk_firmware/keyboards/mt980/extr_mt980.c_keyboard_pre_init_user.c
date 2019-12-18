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
 int /*<<< orphan*/  B5 ; 
 int /*<<< orphan*/  C6 ; 
 int /*<<< orphan*/  C7 ; 
 int /*<<< orphan*/  setPinOutput (int /*<<< orphan*/ ) ; 

void keyboard_pre_init_user(void) {
  /* Set NUMLOCK indicator pin as output */
  setPinOutput(C6);
  /* Set CAPSLOCK indicator pin as output */
  setPinOutput(C7);
  /* Set SCROLLOCK indicator pin as output */
  setPinOutput(B5);
}